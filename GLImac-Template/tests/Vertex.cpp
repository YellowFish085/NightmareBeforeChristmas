#include <gtest/gtest.h>
#include "projet/Vertex.hpp"

TEST(Vertex, init){
  Vertex pt1;
  Vertex pt2(glm::vec3(0), glm::vec2(0), glm::vec3(0));
  EXPECT_EQ(pt1, pt2);

  Vertex pt3(glm::vec3(1), glm::vec2(1,2), glm::vec3(0,1,0));
  EXPECT_EQ(pt3, Vertex(glm::vec3(1), glm::vec2(1,2), glm::vec3(0,1,0)));
}
