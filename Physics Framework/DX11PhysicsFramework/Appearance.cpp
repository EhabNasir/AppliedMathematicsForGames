#include "Appearance.h"

Appearance::Appearance(Geometry geometry, Material material)
    : _geometry(geometry), _material(material)
{
}

Appearance::~Appearance()
{
    _textureRV = nullptr;

    if (_geometry.vertexBuffer) _geometry.vertexBuffer->Release();
    if (_geometry.indexBuffer) _geometry.indexBuffer->Release();
}

void Appearance::Draw(ID3D11DeviceContext* context)
{
    context->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer,
        &_geometry.vertexBufferStride,
        &_geometry.vertexBufferOffset);

    context->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

    context->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
