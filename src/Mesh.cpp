#include <glad/glad.h>
#include "Mesh.h"
#include <GLFW/glfw3.h>
#include <memory>

#include <BRepMesh_IncrementalMesh.hxx>
#include <STEPControl_Reader.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <gp_Pnt.hxx>
#include <TopLoc_Location.hxx>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    : vertices(vertices), indices(indices) 
{
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex positions (layout location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex normals (layout = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Texture coordinates (layout location = 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Mesh::draw() const
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


std::shared_ptr<Mesh> Mesh::loadSTEP(const std::string& filepath) {
    float deflection = 1.0f;
    STEPControl_Reader reader;
    if (reader.ReadFile(filepath.c_str()) != IFSelect_RetDone) {
        std::cerr << "Failed to read STEP file\n";
        return nullptr;
    }

    reader.TransferRoots();
    TopoDS_Shape shape = reader.OneShape();
    if (shape.IsNull()) return nullptr;

    BRepMesh_IncrementalMesh mesh(shape, deflection, true);

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t indexOffset = 0;

    for (TopExp_Explorer exp(shape, TopAbs_FACE); exp.More(); exp.Next()) {
        TopoDS_Face face = TopoDS::Face(exp.Current());
        TopLoc_Location loc;
        Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(face, loc);

        if (!tri.IsNull()) {
            // Vertices: initialize normal to zero so we can accumulate face normals later
            for (int i = 1; i <= tri->NbNodes(); i++) {
                gp_Pnt p = tri->Node(i).Transformed(loc.Transformation());
                Vertex v;
                v.position = glm::vec3(float(p.X()), float(p.Y()), float(p.Z()));
                v.normal   = glm::vec3(0.0f, 0.0f, 0.0f); // placeholder
                v.uv       = glm::vec2(0.0f, 0.0f);       // no UVs available from STEP; set to 0
                vertices.push_back(v);
            }

            // Triangles (note: OpenCASCADE indices are 1-based)
            for (int i = 1; i <= tri->NbTriangles(); i++) {
                Poly_Triangle t = tri->Triangle(i);
                int n1, n2, n3;
                t.Get(n1, n2, n3);
                indices.push_back(indexOffset + static_cast<uint32_t>(n1 - 1));
                indices.push_back(indexOffset + static_cast<uint32_t>(n2 - 1));
                indices.push_back(indexOffset + static_cast<uint32_t>(n3 - 1));
            }

            // advance indexOffset by number of new nodes added for this face
            indexOffset = static_cast<uint32_t>(vertices.size());
        }
    }

    if (vertices.empty() || indices.empty()) {
        std::cerr << "No triangulated geometry found!\n";
        return nullptr;
    }

    // --- Compute normals: accumulate face normals into vertex normals ---
    for (size_t i = 0; i + 2 < indices.size(); i += 3) {
        uint32_t ia = indices[i];
        uint32_t ib = indices[i + 1];
        uint32_t ic = indices[i + 2];

        glm::vec3 &A = vertices[ia].position;
        glm::vec3 &B = vertices[ib].position;
        glm::vec3 &C = vertices[ic].position;

        glm::vec3 edge1 = B - A;
        glm::vec3 edge2 = C - A;
        glm::vec3 faceNormal = glm::cross(edge1, edge2);

        // avoid zero-length normals
        if (glm::length(faceNormal) > 0.0f) {
            faceNormal = glm::normalize(faceNormal);
            vertices[ia].normal += faceNormal;
            vertices[ib].normal += faceNormal;
            vertices[ic].normal += faceNormal;
        }
    }

    // Normalize vertex normals
    for (auto &v : vertices) {
        if (glm::length(v.normal) > 0.0f) v.normal = glm::normalize(v.normal);
        else v.normal = glm::vec3(0.0f, 1.0f, 0.0f); // fallback normal if isolated vertex
    }

    return std::make_shared<Mesh>(vertices, indices);
}


