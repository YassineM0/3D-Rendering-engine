# 🧭 OpenGL Renderer with Camera and STEP Model Loading

**C++ OpenGL rendering framework** built with opengl.
It provides a clean architecture for rendering 3D models — including **STEP (.stp)** files — with an integrated **camera system**, **shader management**, and **real-time user input handling** using **GLFW** and **GLM**.

---

## 🚀 Features

- 🎮 **Interactive 3D Camera** (WASD + Mouse support)
- 🧱 **Mesh Management** with vertex/index buffers
- 🌈 **Custom Shader System** (GLSL vertex & fragment shaders)
- 🪞 **Renderer Core** with OpenGL and GLFW
- 🧩 **STEP File Loading** via `Mesh::loadSTEP()`
- 📸 **Perspective Projection & View Matrix Control**
- 🪶 Lightweight and modular C++ design (Header-only classes)

---

## 🧰 Tech Stack

| Component | Library |
|------------|----------|
| Windowing & Input | [GLFW](https://www.glfw.org/) |
| OpenGL Loader | [GLAD](https://glad.dav1d.de/) |
| Math Library | [GLM](https://github.com/g-truc/glm) |
| Image Loading | [stb_image.h](https://github.com/nothings/stb) |
| File Format | STEP (.stp) support |
| Shaders | GLSL |

---

## 🧠 Project Structure

