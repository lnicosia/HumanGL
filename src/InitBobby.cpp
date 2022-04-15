#include "GLContext.class.hpp"
#include "Object/GLObject.class.hpp"
#include "Object/AssetManager.class.hpp"

using namespace notrealengine;

std::shared_ptr<GLObject> InitBobby(void)
{
  std::cout << "Initializing Bobby..." << std::endl;
  std::shared_ptr<Mesh> mesh(new Mesh(GLContext::cube));
  std::vector<std::shared_ptr<Mesh>> meshes;
  meshes.push_back(mesh);
  Mesh& torso = *mesh;

  torso.setName("Torso");
  torso.setColor(mft::vec3(0.0f, 0.5f, 0.0f));
  torso.localTransform.scale(mft::vec3(0.50f, 0.75f, 0.15f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	head = (*torso.getChildren()[0]);
  head.setName("Head");
  head.setColor(mft::vec3(0.6f, 0.6f, 0.0f));
  head.localTransform.move(mft::vec3(0.125f, 1.025f, -0.5f));
  head.localTransform.scale(mft::vec3(0.75f, 0.45f, 2.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& upperLeftArm = (*torso.getChildren()[1]);
  upperLeftArm.setName("Upper left arm");
  upperLeftArm.setColor(mft::vec3(0.5f, 0.5f, 0.0f));
  upperLeftArm.localTransform.move(mft::vec3(1.375f, 0.95f, 0.0f));
  upperLeftArm.localTransform.scale(mft::vec3(0.35f, 0.475f, 1.0f));
  upperLeftArm.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  upperLeftArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& lowerLeftArm = (*upperLeftArm.getChildren()[0]);
  lowerLeftArm.setName("Lower left arm");
  lowerLeftArm.setColor(mft::vec3(0.6f, 0.6f, 0.0f));
  lowerLeftArm.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	upperRightArm = (*torso.getChildren()[2]);
  upperRightArm.setName("Upper right arm");
  upperRightArm.setColor(mft::vec3(0.5f, 0.5f, 0.0f));
  upperRightArm.localTransform.move(mft::vec3(-0.025f, 0.95f, 0.0f));
  upperRightArm.localTransform.scale(mft::vec3(0.35f, 0.475f, 1.0f));
  upperRightArm.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  upperRightArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& lowerRightArm = (*upperRightArm.getChildren()[0]);
  lowerRightArm.setName("Lower right arm");
  lowerRightArm.setColor(mft::vec3(0.6f, 0.6f, 0.0f));
  lowerRightArm.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	leftThigh = (*torso.getChildren()[3]);
  leftThigh.setName("Left thigh");
  leftThigh.setColor(mft::vec3(0.0f, 0.0f, 0.5f));
  leftThigh.localTransform.move(mft::vec3(0.95f, 0.0f, 0.0f));
  leftThigh.localTransform.scale(mft::vec3(0.35f, 0.5f, 1.0f));
  leftThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  leftThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftCalf = (*leftThigh.getChildren()[0]);
  leftCalf.setName("Left calf");
  leftCalf.setColor(mft::vec3(0.0f, 0.0f, 0.6f));
  leftCalf.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  torso.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightThigh = (*torso.getChildren()[4]);
  rightThigh.setName("Right thigh");
  rightThigh.setColor(mft::vec3(0.0f, 0.0f, 0.5f));
  rightThigh.localTransform.move(mft::vec3(0.4f, 0.0f, 0.0f));
  rightThigh.localTransform.scale(mft::vec3(0.35f, 0.5f, 1.0f));
  rightThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  rightThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightCalf = (*rightThigh.getChildren()[0]);
  rightCalf.setName("Right calf");
  rightCalf.setColor(mft::vec3(0.0f, 0.0f, 0.6f));
  rightCalf.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));

  std::shared_ptr<GLObject>	character(new GLObject(meshes));
  character->setName("Bobby");
  character->setShader(GLContext::getShader("color"));
  character->transform.move(mft::vec3(-0.25f, 1.15f, 0.0f));

  AssetManager::getInstance().addAsset(character);

  return character;
}

std::shared_ptr<Animation> InitBobbyWalking(void)
{
  std::map<std::string, Bone> bones;
  std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
  std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
  std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 0.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, -3.0f), 4000.0));
  Bone torso("Torso", positions, rotations, scales);
  bones["Torso"] = torso;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(15.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(15.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 4000.0));
  Bone upperRightArm("Upper right arm", positions, rotations, scales);
  bones["Upper right arm"] = upperRightArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 4000.0));
  Bone lowerRightArm("Lower right arm", positions, rotations, scales);
  bones["Lower right arm"] = lowerRightArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(15.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(15.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(15.0f)), 4000.0));
  Bone upperLeftArm("Upper left arm", positions, rotations, scales);
  bones["Upper left arm"] = upperLeftArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-15.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 4000.0));
  Bone lowerLeftArm("Lower left arm", positions, rotations, scales);
  bones["Lower left arm"] = lowerLeftArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(20.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(20.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 4000.0));
  Bone rightThigh("Right thigh", positions, rotations, scales);
  bones["Right thigh"] = rightThigh;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(30.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(30.0f)), 1750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(30.0f)), 3750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 4000.0));

  Bone rightCalf("Right calf", positions, rotations, scales);
  bones["Right calf"] = rightCalf;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(20.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(20.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(20.0f)), 4000.0));
  Bone leftThigh("Left thigh", positions, rotations, scales);
  bones["Left thigh"] = leftThigh;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(30.0f)), 750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 2000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(30.0f)), 2750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 3000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 4000.0));
  Bone leftCalf("Left calf", positions, rotations, scales);
  bones["Left calf"] = leftCalf;

  return std::shared_ptr<Animation>(new Animation("Bobby walking", bones));
}

std::shared_ptr<Animation> InitBobbyJumping(void)
{
  std::map<std::string, Bone> bones;
  std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
  std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
  std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 0.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, -0.2f, 0.0f), 500.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.5f, 0.0f), 750.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.75f, 0.0f), 1000.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.5f, 0.0f), 1125.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 1250.0));
  Bone torso("Torso", positions, rotations, scales);
  bones["Torso"] = torso;

  // Upper boddy

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, -1.0f), mft::radians(30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1250.0));

  Bone upperRightArm("Upper right arm", positions, rotations, scales);
  bones["Upper right arm"] = upperRightArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 750.0));
  Bone lowerRightArm("Lower right arm", positions, rotations, scales);
  bones["Lower right arm"] = lowerRightArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 1.0f), mft::radians(30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-40.0f)), 750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-40.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1250.0));
  Bone upperLeftArm("Upper left arm", positions, rotations, scales);
  bones["Upper left arm"] = upperLeftArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 750.0));
  Bone lowerLeftArm("Lower left arm", positions, rotations, scales);
  bones["Lower left arm"] = lowerLeftArm;

  //  Lower boddy

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone leftThigh("Left thigh", positions, rotations, scales);
  bones["Left thigh"] = leftThigh;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(60.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone leftCalf("Left calf", positions, rotations, scales);
  bones["Left calf"] = leftCalf;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone rightThigh("Right thigh", positions, rotations, scales);
  bones["Right thigh"] = rightThigh;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(60.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone rightCalf("Right calf", positions, rotations, scales);
  bones["Right calf"] = rightCalf;

  return std::shared_ptr<Animation>(new Animation("Bobby jumping", bones));
}


std::shared_ptr<Animation> InitBobbyIdle(void)
{
  std::map<std::string, Bone> bones;
  std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
  std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
  std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 0.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.05f, 0.0f), 500.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 1000.0));
  Bone torso("Torso", positions, rotations, scales);
  bones["Torso"] = torso;

  positions.clear();
  rotations.clear();
  scales.clear();
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 0.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, -0.05f, 0.0f), 500.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 1000.0));
  Bone leftCalf("Left calf", positions, rotations, scales);
  bones["Left calf"] = leftCalf;

  positions.clear();
  rotations.clear();
  scales.clear();
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 0.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, -0.05f, 0.0f), 500.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 1000.0));
  Bone rightCalf("Right calf", positions, rotations, scales);
  bones["Right calf"] = rightCalf;

  return std::shared_ptr<Animation>(new Animation("Bobby idle", bones));
}
