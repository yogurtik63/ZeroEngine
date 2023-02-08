#include "VertexBufferLayout.h"

namespace Renderer {
	VertexBufferLayout::VertexBufferLayout()
		: m_stride(0)
	{

	}

	void VertexBufferLayout::reserveElement(const size_t count) {
		m_layoutElements.reserve(count);
	}
	
	void VertexBufferLayout::addElementLayoutFloat(GLint count, GLboolean normalized) {
		m_layoutElements.push_back({ count, GL_FLOAT, normalized, (unsigned int) (count * sizeof(GLfloat)) });
		m_stride += m_layoutElements.back().size;
	}
}