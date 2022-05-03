#include "GLContext.class.hpp"
#include "Object/GLObject.class.hpp"
#include "Object/AssetManager.class.hpp"

using namespace notrealengine;

std::shared_ptr<GLObject> InitRoundyPlus(void)
{
  std::cout << "Initializing Roundy Plus..." << std::endl;
  std::shared_ptr<Mesh> mesh(new Mesh(GLContext::sphere));
  std::vector<std::shared_ptr<Mesh>> meshes;
  meshes.push_back(mesh);
  Mesh& chest = *mesh;

  chest.setName("Chest");
  chest.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  chest.localTransform.move(mft::vec3(0.0f, 0.5f, 0.0f));
  chest.localTransform.setScale(mft::vec3(0.6f, 0.5f, 0.5f));

  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	neck = (*chest.getChildren()[0]);
  neck.setName("Neck");
  neck.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  neck.localTransform.move(mft::vec3(0.35f, 0.885f, 0.3f));
  neck.localTransform.setScale(mft::vec3(0.3f, 0.25f, 0.4f));

  neck.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	head = (*neck.getChildren()[0]);
  head.setName("Head");
  head.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  head.localTransform.move(mft::vec3(-0.8f, 0.7f, -0.3f));
  head.localTransform.setScale(mft::vec3(2.5f, 4.0f, 2.2f));

  //    Upper boddy

  //    Left side
  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftShoulder = (*chest.getChildren()[1]);
  leftShoulder.setName("Left shoulder");
  leftShoulder.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftShoulder.localTransform.move(mft::vec3(1.4f, 0.95f, 0.3f));
  leftShoulder.localTransform.setScale(mft::vec3(0.5f, 0.6f, 0.6f));
  leftShoulder.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 180.0f), AngleDegrees));

  leftShoulder.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& upperLeftArm = (*leftShoulder.getChildren()[0]);
  upperLeftArm.setName("Upper left arm");
  upperLeftArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  upperLeftArm.localTransform.move(mft::vec3(0.1f, 0.75f, 0.0f));
  upperLeftArm.localTransform.setScale(mft::vec3(0.8f, 1.30f, 1.0f));

  upperLeftArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftElbow = (*upperLeftArm.getChildren()[0]);
  leftElbow.setName("Left elbow");
  leftElbow.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftElbow.localTransform.move(mft::vec3(0.085f, 0.8f, 0.0f));
  leftElbow.localTransform.setScale(mft::vec3(0.9f, 0.6f, 1.0f));
  leftElbow.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  leftElbow.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& lowerLeftArm = (*leftElbow.getChildren()[0]);
  lowerLeftArm.setName("Lower left arm");
  lowerLeftArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  lowerLeftArm.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  lowerLeftArm.localTransform.setScale(mft::vec3(0.8f, 1.5f, 1.0f));
  lowerLeftArm.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  lowerLeftArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftHand = (*lowerLeftArm.getChildren()[0]);
  leftHand.setName("Left hand");
  leftHand.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  leftHand.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  leftHand.localTransform.setScale(mft::vec3(0.9f, 0.8f, 1.0f));

  //    Right side
  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightShoulder = (*chest.getChildren()[2]);
  rightShoulder.setName("Right shoulder");
  rightShoulder.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightShoulder.localTransform.move(mft::vec3(0.1f, 0.95f, 0.3f));
  rightShoulder.localTransform.setScale(mft::vec3(0.5f, 0.6f, 0.6f));
  rightShoulder.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 180.0f), AngleDegrees));

  rightShoulder.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& upperRightArm = (*rightShoulder.getChildren()[0]);
  upperRightArm.setName("Upper right arm");
  upperRightArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  upperRightArm.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  upperRightArm.localTransform.setScale(mft::vec3(0.8f, 1.30f, 1.0f));

  upperRightArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightElbow = (*upperRightArm.getChildren()[0]);
  rightElbow.setName("Elbow");
  rightElbow.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightElbow.localTransform.move(mft::vec3(0.085f, 0.8f, 0.0f));
  rightElbow.localTransform.setScale(mft::vec3(0.9f, 0.6f, 1.0f));
  rightElbow.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  rightElbow.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& lowerRightArm = (*rightElbow.getChildren()[0]);
  lowerRightArm.setName("Lower right arm");
  lowerRightArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  lowerRightArm.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  lowerRightArm.localTransform.setScale(mft::vec3(0.8f, 1.5f, 1.0f));
  lowerRightArm.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  lowerRightArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightHand = (*lowerRightArm.getChildren()[0]);
  rightHand.setName("Right hand");
  rightHand.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  rightHand.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  rightHand.localTransform.setScale(mft::vec3(0.9f, 0.8f, 1.0f));

  //    Legs

  //    Lower boddy

  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	abdomen = (*chest.getChildren()[3]);
  abdomen.setName("Abdomen");
  abdomen.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  abdomen.localTransform.move(mft::vec3(0.1f, -0.5f, 0.0f));
  abdomen.localTransform.setScale(mft::vec3(0.8f, 0.9f, 0.8f));

  abdomen.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	pelvis = (*abdomen.getChildren()[0]);
  pelvis.setName("Pelvis");
  pelvis.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  pelvis.localTransform.move(mft::vec3(-0.1f, -0.6f, 0.0f));
  pelvis.localTransform.setScale(mft::vec3(1.2f, 1.0f, 1.2f));

  pelvis.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh&	leftThigh = (*pelvis.getChildren()[0]);
  leftThigh.setName("Left thigh");
  leftThigh.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  leftThigh.localTransform.move(mft::vec3(1.05f, 0.2f, 0.3f));
  leftThigh.localTransform.setScale(mft::vec3(0.5f, 1.0f, 0.6f));
  leftThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  leftThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftKnee = (*leftThigh.getChildren()[0]);
  leftKnee.setName("Left knee");
  leftKnee.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftKnee.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  leftKnee.localTransform.setScale(mft::vec3(0.8f, 0.6f, 1.0f));

  leftKnee.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftCalf = (*leftKnee.getChildren()[0]);
  leftCalf.setName("Left calf");
  leftCalf.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  leftCalf.localTransform.move(mft::vec3(0.05f, 0.8f, 0.1f));
  leftCalf.localTransform.setScale(mft::vec3(0.9f, 1.9f, 0.8f));

  leftCalf.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& leftFoot = (*leftCalf.getChildren()[0]);
  leftFoot.setName("Left foot");
  leftFoot.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftFoot.localTransform.move(mft::vec3(0.0f, 0.8f, 0.0f));
  leftFoot.localTransform.setScale(mft::vec3(1.0f, 0.3f, 2.5f));

  pelvis.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightThigh = (*pelvis.getChildren()[1]);
  rightThigh.setName("Right thigh");
  rightThigh.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  rightThigh.localTransform.move(mft::vec3(0.45f, 0.2f, 0.3f));
  rightThigh.localTransform.setScale(mft::vec3(0.5f, 1.0f, 0.6f));
  rightThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  rightThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightKnee = (*rightThigh.getChildren()[0]);
  rightKnee.setName("Right knee");
  rightKnee.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightKnee.localTransform.move(mft::vec3(0.1f, 0.8f, 0.0f));
  rightKnee.localTransform.setScale(mft::vec3(0.8f, 0.6f, 1.0f));

  rightKnee.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightCalf = (*rightKnee.getChildren()[0]);
  rightCalf.setName("Right calf");
  rightCalf.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  rightCalf.localTransform.move(mft::vec3(0.05f, 0.8f, 0.0f));
  rightCalf.localTransform.setScale(mft::vec3(0.9f, 1.9f, 0.8f));

  rightCalf.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::sphere)));
  Mesh& rightFoot = (*rightCalf.getChildren()[0]);
  rightFoot.setName("Right foot");
  rightFoot.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightFoot.localTransform.move(mft::vec3(0.0f, 0.8f, 0.0f));
  rightFoot.localTransform.setScale(mft::vec3(1.0f, 0.3f, 2.5f));

  std::shared_ptr<GLObject>	character(new GLObject(meshes));
  character->setName("Roundy Plus");
  character->setShader(GLContext::getShader("color"));
  character->transform.move(mft::vec3(-0.25f, 1.15f, 0.0f));

  AssetManager::getInstance().addAsset(character);

  return character;
}
