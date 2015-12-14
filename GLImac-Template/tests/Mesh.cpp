#include <gtest/gtest.h>
#include "projet/Mesh.hpp"

TEST(Mesh, init_setters){
  Mesh m1;
  ASSERT_FALSE(m1.getVertices());
  ASSERT_FALSE(m1.getIndices());
  EXPECT_EQ(m1.getMaterialIndex(), UNDEFINED);

  m1.setMaterialIndex(0);
  ASSERT_FALSE(m1.getMaterialIndex() == UNDEFINED);
  EXPECT_EQ(m1.getMaterialIndex(), 0);

  m1.addVertex(Vertex(glm::vec3(1,1,1),
                      glm::vec2(1,1),
                      glm::vec3(1,1,1)));

  m1.addIndex(1);

  std::vector<Vertex> v;
  v.push_back(Vertex(glm::vec3(1,1,1),
                      glm::vec2(1,1),
                      glm::vec3(1,1,1)));

  std::vector<uint32_t> i;
  i.push_back(1);

  Mesh m2(v, i, 0);

  EXPECT_EQ(m1, m2);
}

TEST(Mesh, push_back) {
  Mesh m1;
  Vertex v(glm::vec3(1,1,1),
          glm::vec2(1,1),
          glm::vec3(1,1,1));

  m1.addVertex(v);

  v = Vertex(glm::vec3(2,2,2),
             glm::vec2(2,2),
             glm::vec3(2,2,2));

  ASSERT_FALSE(m1.getVertices() == &v);
}

TEST(Mesh, getters) {
  std::vector<Vertex> v;
  v.push_back(Vertex(glm::vec3(1,1,1),
                      glm::vec2(1,1),
                      glm::vec3(1,1,1)));

  std::vector<uint32_t> i;
  i.push_back(1);

  Mesh m(v, i, 0);

  EXPECT_EQ(*(m.getVertices()), *(v.data()));
  EXPECT_EQ(*(m.getIndices()), *(i.data()));
}
