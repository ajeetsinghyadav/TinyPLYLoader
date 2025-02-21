
#include "ply_loader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstring>

void PlyLoader_C::LoadPLY(const std::string &filename)
{
    try
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        tinyply::PlyFile plyFile;
        plyFile.parse_header(file);

        std::shared_ptr<tinyply::PlyData> vertices;
        std::shared_ptr<tinyply::PlyData> faces;
        std::shared_ptr<tinyply::PlyData>  vertex_scalar;
        std::shared_ptr<tinyply::PlyData> face_scalar;

        vertices = plyFile.request_properties_from_element("vertex", {"x", "y", "z"});
        try
        {
            vertex_scalar = plyFile.request_properties_from_element("vertex", {"vertex_scalar"});
        }
        catch (...)
        {
            std::cerr << "Warning: No vertex_scalar found.\n";
        }

        faces = plyFile.request_properties_from_element("face", {"vertex_indices"});
        try
        {
            face_scalar = plyFile.request_properties_from_element("face", {"face_scalar"});
        }
        catch (...)
        {
            std::cerr << "Warning: No face_scalar found.\n";
        }

        plyFile.read(file);
        std::vector<float> vertexBuffer(vertices->count * 3);
        std::memcpy(vertexBuffer.data(), vertices->buffer.get(), vertices->buffer.size_bytes());

        std::cout << "Loaded " << vertices->count << " vertices.\n";
        for (size_t i = 0; i < vertices->count; i++)
        {
            std::cout << "Vertex " << i << ": ("
                      << vertexBuffer[i * 3] << ", "
                      << vertexBuffer[i * 3 + 1] << ", "
                      << vertexBuffer[i * 3 + 2] << ")\n";
        }

        if (vertex_scalar)
        {
            std::vector<float> vertexScalarBuffer(vertex_scalar->count);
            std::memcpy(vertexScalarBuffer.data(), vertex_scalar->buffer.get(), vertex_scalar->buffer.size_bytes());
            for (size_t i = 0; i < vertex_scalar->count; i++)
            {
                std::cout << "Vertex Scalar " << i << ": " << vertexScalarBuffer[i] << "\n";
            }
        }

        std::vector<int> faceBuffer(faces->count * 3);
        std::memcpy(faceBuffer.data(), faces->buffer.get(), faces->buffer.size_bytes());

        std::cout << "Loaded " << faces->count << " faces.\n";
        for (size_t i = 0; i < faces->count; i++)
        {
            std::cout << "Face " << i << ": ("
                      << faceBuffer[i * 3] << ", "
                      << faceBuffer[i * 3 + 1] << ", "
                      << faceBuffer[i * 3 + 2] << ")\n";
        }

        if (face_scalar)
        {
            std::vector<float> faceScalarBuffer(face_scalar->count);
            std::memcpy(faceScalarBuffer.data(), face_scalar->buffer.get(), face_scalar->buffer.size_bytes());
            for (size_t i = 0; i < face_scalar->count; i++)
            {
                std::cout << "Face Scalar " << i << ": " << faceScalarBuffer[i] << "\n";
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading PLY: " << e.what() << std::endl;
    }
}
