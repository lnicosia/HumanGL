#include "GLContext.class.hpp"
#include "Object/GLObject.class.hpp"
#include "Object/AssetManager.class.hpp"

using namespace notrealengine;

std::shared_ptr<GLObject> InitRoundy(void)
{
  std::cout << "Initializing Roundy..." << std::endl;
  std::shared_ptr<Mesh> mesh(new Mesh(GLContext::sphere));
  std::vector<std::shared_ptr<Mesh>> meshes;
  meshes.push_back(mesh);
  Mesh& torso = *mesh;

  torso.setName("Torso");
  torso.setColor(mft::vec4(0.0f, 0.5f, 0.0f, 1.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	head = (*torso.getChildren()[0]);
  head.setName("Head");
  head.setColor(mft::vec4(0.6f, 0.6f, 0.0f, 1.0f));
  head.localTransform.move(mft::vec3(0.2f, 1.0f, 0.3f));
  head.localTransform.setScale(mft::vec3(0.6f, 0.6f, 0.6f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& upperLeftArm = (*torso.getChildren()[1]);
  upperLeftArm.setName("Upper left arm");
  upperLeftArm.setColor(mft::vec4(0.5f, 0.5f, 0.0f, 1.0f));
  upperLeftArm.localTransform.move(mft::vec3(1.3f, 0.95f, 0.4f));
  upperLeftArm.localTransform.setScale(mft::vec3(0.3f, 0.5f, 0.3f));
  upperLeftArm.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  upperLeftArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& lowerLeftArm = (*upperLeftArm.getChildren()[0]);
  lowerLeftArm.setName("Lower left arm");
  lowerLeftArm.setColor(mft::vec4(0.6f, 0.6f, 0.0f, 1.0f));
  lowerLeftArm.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	upperRightArm = (*torso.getChildren()[2]);
  upperRightArm.setName("Upper right arm");
  upperRightArm.setColor(mft::vec4(0.5f, 0.5f, 0.0f, 1.0f));
  upperRightArm.localTransform.move(mft::vec3(0.01f, 0.9f, 0.4f));
  upperRightArm.localTransform.setScale(mft::vec3(0.3f, 0.5f, 0.3f));
  upperRightArm.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  upperRightArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& lowerRightArm = (*upperRightArm.getChildren()[0]);
  lowerRightArm.setName("Lower right arm");
  lowerRightArm.setColor(mft::vec4(0.6f, 0.6f, 0.0f, 1.0f));
  lowerRightArm.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	leftThigh = (*torso.getChildren()[3]);
  leftThigh.setName("Left thigh");
  leftThigh.setColor(mft::vec4(0.0f, 0.0f, 0.5f, 1.0f));
  leftThigh.localTransform.move(mft::vec3(0.9f, 0.1f, 0.4f));
  leftThigh.localTransform.setScale(mft::vec3(0.35f, 0.5f, 0.3f));
  leftThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  leftThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftCalf = (*leftThigh.getChildren()[0]);
  leftCalf.setName("Left calf");
  leftCalf.setColor(mft::vec4(0.0f, 0.0f, 0.6f, 1.0f));
  leftCalf.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightThigh = (*torso.getChildren()[4]);
  rightThigh.setName("Right thigh");
  rightThigh.setColor(mft::vec4(0.0f, 0.0f, 0.5f, 1.0f));
  rightThigh.localTransform.move(mft::vec3(0.4f, 0.1f, 0.4f));
  rightThigh.localTransform.setScale(mft::vec3(0.35f, 0.5f, 0.3f));
  rightThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  rightThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightCalf = (*rightThigh.getChildren()[0]);
  rightCalf.setName("Right calf");
  rightCalf.setColor(mft::vec4(0.0f, 0.0f, 0.6f, 1.0f));
  rightCalf.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  std::shared_ptr<GLObject>	character(new GLObject(meshes));
  character->setName("Roundy");
  character->setShader(GLContext::getShader("color"));
  character->transform.move(mft::vec3(-0.25f, 1.15f, 0.0f));

  AssetManager::getInstance().addAsset(character);

  return character;
}