// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef B2_CHAIN_SHAPE_H
#define B2_CHAIN_SHAPE_H

#include "b2_shape.h"

class b2EdgeShape;

/// A chain shape is a free form sequence of line segments.
/// The chain has two-sided collision, so you can use inside and outside collision.
/// Therefore, you may use any winding order.
/// The chain can also be configured as a one-sided loop. This allows for smooth
/// collision by using edge connectivity.
/// Since there may be many vertices, they are allocated using b2Alloc.
/// Connectivity information is used to create smooth collisions.
/// WARNING: The chain will not collide properly if there are self-intersections.
class b2ChainShape : public b2Shape
{
public:
	b2ChainShape();

	/// The destructor frees the vertices using b2Free.
	~b2ChainShape();

	/// Clear all data.
	void Clear();

	/// Create a two-sided loop.
	/// @param vertices an array of vertices, these are copied
	/// @param count the vertex count
	void CreateTwoSidedLoop(const b2Vec2* vertices, int32 count);

	/// Create a two-sided chain with isolated end vertices.
	/// @param vertices an array of vertices, these are copied
	/// @param count the vertex count
	void CreateTwoSidedChain(const b2Vec2* vertices, int32 count);

	/// Create a one-sided loop with smooth collision. A counter-clockwise
	/// winding order creates outward normals.
	/// @param vertices an array of vertices, these are copied
	/// @param count the vertex count
	void CreateOneSidedLoop(const b2Vec2* vertices, int32 count);

	/// Implement b2Shape. Vertices are cloned using b2Alloc.
	b2Shape* Clone(b2BlockAllocator* allocator) const override;

	/// @see b2Shape::GetChildCount
	int32 GetChildCount() const override;

	/// Get a child edge.
	void GetChildEdge(b2EdgeShape* edge, int32 index) const;

	/// This always return false.
	/// @see b2Shape::TestPoint
	bool TestPoint(const b2Transform& transform, const b2Vec2& p) const override;

	/// Implement b2Shape.
	bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
					const b2Transform& transform, int32 childIndex) const override;

	/// @see b2Shape::ComputeAABB
	void ComputeAABB(b2AABB* aabb, const b2Transform& transform, int32 childIndex) const override;

	/// Chains have zero mass.
	/// @see b2Shape::ComputeMass
	void ComputeMass(b2MassData* massData, float density) const override;

	/// The vertices. Owned by this class.
	b2Vec2* m_vertices;

	/// The vertex count.
	int32 m_count;

	bool m_loop;
};

inline b2ChainShape::b2ChainShape()
{
	m_type = e_chain;
	m_radius = b2_polygonRadius;
	m_vertices = nullptr;
	m_count = 0;
}

#endif
