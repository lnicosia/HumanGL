#include "GLContext.class.hpp"
#include "Object/GLObject.class.hpp"
#include "Object/AssetManager.class.hpp"

using namespace notrealengine;

std::shared_ptr<GLObject> InitBobbyPlus(void)
{
  std::cout << "Initializing Bobby Plus..." << std::endl;
  std::shared_ptr<Mesh> mesh(new Mesh(GLContext::cube));
  std::vector<std::shared_ptr<Mesh>> meshes;
  meshes.push_back(mesh);
  Mesh& chest = *mesh;

  chest.setName("Chest");
  chest.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  chest.localTransform.move(mft::vec3(0.0f, 0.5f, 0.0f));
  chest.localTransform.setScale(mft::vec3(0.50f, 0.25f, 0.15f));

  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	neck = (*chest.getChildren()[0]);
  neck.setName("Neck");
  neck.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  neck.localTransform.move(mft::vec3(0.35f, 0.985f, 0.0f));
  neck.localTransform.setScale(mft::vec3(0.3f, 0.25f, 1.0f));

  neck.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	head = (*neck.getChildren()[0]);
  head.setName("Head");
  head.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  head.localTransform.move(mft::vec3(-0.3f, 0.995f, -0.3f));
  head.localTransform.setScale(mft::vec3(1.6f, 4.0f, 1.6f));

  //    Upper boddy

  //    Left side
  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftShoulder = (*chest.getChildren()[1]);
  leftShoulder.setName("Left shoulder");
  leftShoulder.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftShoulder.localTransform.move(mft::vec3(1.3f, 0.95f, 0.0f));
  leftShoulder.localTransform.setScale(mft::vec3(0.3f, 0.6f, 1.0f));
  leftShoulder.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 180.0f), AngleDegrees));

  leftShoulder.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& upperLeftArm = (*leftShoulder.getChildren()[0]);
  upperLeftArm.setName("Upper left arm");
  upperLeftArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  upperLeftArm.localTransform.move(mft::vec3(0.1f, 0.95f, 0.0f));
  upperLeftArm.localTransform.setScale(mft::vec3(0.8f, 1.30f, 1.0f));

  upperLeftArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftElbow = (*upperLeftArm.getChildren()[0]);
  leftElbow.setName("Left elbow");
  leftElbow.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftElbow.localTransform.move(mft::vec3(0.085f, 1.0f, 0.0f));
  leftElbow.localTransform.setScale(mft::vec3(0.9f, 0.6f, 1.0f));
  leftElbow.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  leftElbow.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& lowerLeftArm = (*leftElbow.getChildren()[0]);
  lowerLeftArm.setName("Lower left arm");
  lowerLeftArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  lowerLeftArm.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  lowerLeftArm.localTransform.setScale(mft::vec3(0.8f, 1.5f, 1.0f));
  lowerLeftArm.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  lowerLeftArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftHand = (*lowerLeftArm.getChildren()[0]);
  leftHand.setName("Left hand");
  leftHand.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  leftHand.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  leftHand.localTransform.setScale(mft::vec3(0.9f, 0.8f, 1.0f));

  //    Right side
  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightShoulder = (*chest.getChildren()[2]);
  rightShoulder.setName("Right shoulder");
  rightShoulder.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightShoulder.localTransform.move(mft::vec3(0.0f, 0.95f, 0.0f));
  rightShoulder.localTransform.setScale(mft::vec3(0.3f, 0.6f, 1.0f));
  rightShoulder.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 180.0f), AngleDegrees));

  rightShoulder.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& upperRightArm = (*rightShoulder.getChildren()[0]);
  upperRightArm.setName("Upper right arm");
  upperRightArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  upperRightArm.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  upperRightArm.localTransform.setScale(mft::vec3(0.8f, 1.30f, 1.0f));

  upperRightArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightElbow = (*upperRightArm.getChildren()[0]);
  rightElbow.setName("Elbow");
  rightElbow.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightElbow.localTransform.move(mft::vec3(0.085f, 1.0f, 0.0f));
  rightElbow.localTransform.setScale(mft::vec3(0.9f, 0.6f, 1.0f));
  rightElbow.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  rightElbow.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& lowerRightArm = (*rightElbow.getChildren()[0]);
  lowerRightArm.setName("Lower right arm");
  lowerRightArm.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  lowerRightArm.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  lowerRightArm.localTransform.setScale(mft::vec3(0.8f, 1.5f, 1.0f));
  lowerRightArm.localTransform.rotate(mft::quat::rotate(mft::vec3(10.0f, 0.0f, 0.0f), AngleDegrees));

  lowerRightArm.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightHand = (*lowerRightArm.getChildren()[0]);
  rightHand.setName("Right hand");
  rightHand.setColor(mft::vec4(0.886f, 0.529f, 0.263f, 1.0f));
  rightHand.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  rightHand.localTransform.setScale(mft::vec3(0.9f, 0.8f, 1.0f));

  //    Legs

  //    Lower boddy

  chest.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	abdomen = (*chest.getChildren()[3]);
  abdomen.setName("Abdomen");
  abdomen.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  abdomen.localTransform.move(mft::vec3(0.1f, -0.9f, 0.0f));
  abdomen.localTransform.setScale(mft::vec3(0.8f, 0.9f, 0.8f));

  abdomen.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	pelvis = (*abdomen.getChildren()[0]);
  pelvis.setName("Pelvis");
  pelvis.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  pelvis.localTransform.move(mft::vec3(-0.1f, -1.0f, 0.0f));
  pelvis.localTransform.setScale(mft::vec3(1.2f, 1.0f, 1.2f));

  pelvis.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh&	leftThigh = (*pelvis.getChildren()[0]);
  leftThigh.setName("Left thigh");
  leftThigh.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  leftThigh.localTransform.move(mft::vec3(0.95f, 0.0f, 0.0f));
  leftThigh.localTransform.setScale(mft::vec3(0.4f, 1.0f, 1.0f));
  leftThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  leftThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftKnee = (*leftThigh.getChildren()[0]);
  leftKnee.setName("Left knee");
  leftKnee.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftKnee.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  leftKnee.localTransform.setScale(mft::vec3(0.8f, 0.6f, 1.0f));

  leftKnee.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftCalf = (*leftKnee.getChildren()[0]);
  leftCalf.setName("Left calf");
  leftCalf.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  leftCalf.localTransform.move(mft::vec3(0.05f, 1.0f, 0.1f));
  leftCalf.localTransform.setScale(mft::vec3(0.9f, 1.9f, 0.8f));

  leftCalf.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& leftFoot = (*leftCalf.getChildren()[0]);
  leftFoot.setName("Left foot");
  leftFoot.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  leftFoot.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));
  leftFoot.localTransform.setScale(mft::vec3(1.0f, 0.3f, 2.5f));

  pelvis.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightThigh = (*pelvis.getChildren()[1]);
  rightThigh.setName("Right thigh");
  rightThigh.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  rightThigh.localTransform.move(mft::vec3(0.45f, 0.0f, 0.0f));
  rightThigh.localTransform.setScale(mft::vec3(0.4f, 1.0f, 1.0f));
  rightThigh.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 1.0f), mft::radians(180.0f)));

  rightThigh.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightKnee = (*rightThigh.getChildren()[0]);
  rightKnee.setName("Right knee");
  rightKnee.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightKnee.localTransform.move(mft::vec3(0.1f, 1.0f, 0.0f));
  rightKnee.localTransform.setScale(mft::vec3(0.8f, 0.6f, 1.0f));

  rightKnee.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightCalf = (*rightKnee.getChildren()[0]);
  rightCalf.setName("Right calf");
  rightCalf.setColor(mft::vec4(0.15f, 0.15f, 0.15f, 1.0f));
  rightCalf.localTransform.move(mft::vec3(0.05f, 1.0f, 0.0f));
  rightCalf.localTransform.setScale(mft::vec3(0.9f, 1.9f, 0.8f));

  rightCalf.addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
  Mesh& rightFoot = (*rightCalf.getChildren()[0]);
  rightFoot.setName("Right foot");
  rightFoot.setColor(mft::vec4(0.32f, 0.117f, 0.117f, 1.0f));
  rightFoot.localTransform.move(mft::vec3(0.0f, 1.0f, 0.0f));
  rightFoot.localTransform.setScale(mft::vec3(1.0f, 0.3f, 2.5f));

  std::shared_ptr<GLObject>	character(new GLObject(meshes));
  character->setName("Bobby Plus");
  character->setShader(GLContext::getShader("color"));
  character->transform.move(mft::vec3(-0.25f, 1.15f, 0.0f));

  AssetManager::getInstance().addAsset(character);

  return character;
}


std::shared_ptr<Animation> InitBobbyPlusWalking(void)
{
    std::map<std::string, Bone> bones;
    std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
    std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
    std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, -0.1f, 0.025f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, -0.2f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, -0.1f, -0.03f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, 0.0f, -0.07f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, 0.1f, -0.025f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, 0.2f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, 0.1f, 0.03f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, 0.0f, 0.07f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.05f, -0.1f, 0.025f)), 800.0));
    Bone chest("Chest", positions, rotations, scales);
    bones["Chest"] = chest;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, -0.9f, -0.1f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.8f, -0.5f, -0.05f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, -0.2f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.7f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.03f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.4f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, -0.9f, -0.1f)), 800.0));
    Bone upperRightArm("Upper right arm", positions, rotations, scales);
    bones["Upper right arm"] = upperRightArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.25f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.2f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.0f)), 800.0));
    Bone lowerRightArm("Lower right arm", positions, rotations, scales);
    bones["Lower right arm"] = lowerRightArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.7f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.03f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.4f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.9f, 0.1f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.8f, 0.5f, 0.05f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.2f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.7f, 0.0f, 0.0f)), 800.0));
    Bone upperLeftArm("Upper left arm", positions, rotations, scales);
    bones["Upper left arm"] = upperLeftArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.6f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.25f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.2f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.6f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.3f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.0f, 0.0f)), 800.0));
    Bone lowerLeftArm("Lower left arm", positions, rotations, scales);
    bones["Lower left arm"] = lowerLeftArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.4f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.6f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.9f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.8f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.4f, 0.0f, 0.0f)), 800.0));
    Bone rightThigh("Right thigh", positions, rotations, scales);
    bones["Right thigh"] = rightThigh;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.8f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.2f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 800.0));

    Bone rightCalf("Right calf", positions, rotations, scales);
    bones["Right calf"] = rightCalf;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.8f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.4f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.6f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.9f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.7f, 0.0f, 0.0f)), 800.0));
    Bone leftThigh("Left thigh", positions, rotations, scales);
    bones["Left thigh"] = leftThigh;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 100.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 300.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 500.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.8f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.2f, 0.0f, 0.0f)), 700.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.1f, 0.0f, 0.0f)), 800.0));
    Bone leftCalf("Left calf", positions, rotations, scales);
    bones["Left calf"] = leftCalf;

    std::shared_ptr<Animation> anim =
        std::shared_ptr<Animation>(new Animation("Bobby Plus walking", bones));
    AssetManager::getInstance().addAsset(anim);
    return anim;
}

std::shared_ptr<Animation> InitBobbyPlusJumping(void)
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
  Bone chest("Chest", positions, rotations, scales);
  bones["Chest"] = chest;

  // Upper boddy

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, -1.0f), mft::radians(30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1250.0));

  Bone upperRightArm("Upper right arm", positions, rotations, scales);
  bones["Upper right arm"] = upperRightArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 750.0));
  Bone lowerRightArm("Lower right arm", positions, rotations, scales);
  bones["Lower right arm"] = lowerRightArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 1.0f), mft::radians(30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-40.0f)), 750.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-40.0f)), 1000.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 1250.0));
  Bone upperLeftArm("Upper left arm", positions, rotations, scales);
  bones["Upper left arm"] = upperLeftArm;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-20.0f)), 750.0));
  Bone lowerLeftArm("Lower left arm", positions, rotations, scales);
  bones["Lower left arm"] = lowerLeftArm;

  //  Lower boddy

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone leftThigh("Left thigh", positions, rotations, scales);
  bones["Left thigh"] = leftThigh;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(60.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone leftCalf("Left calf", positions, rotations, scales);
  bones["Left calf"] = leftCalf;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(-30.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone rightThigh("Right thigh", positions, rotations, scales);
  bones["Right thigh"] = rightThigh;

  positions.clear();
  rotations.clear();
  scales.clear();
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 0.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(60.0f)), 500.0));
  rotations.push_back(QuatKeyFrame(mft::quat::rotation(mft::vec3(-1.0f, 0.0f, 0.0f), mft::radians(0.0f)), 750.0));
  Bone rightCalf("Right calf", positions, rotations, scales);
  bones["Right calf"] = rightCalf;

  std::shared_ptr<Animation> anim =
    std::shared_ptr<Animation>(new Animation("Bobby Plus jumping", bones));
  AssetManager::getInstance().addAsset(anim);
  return anim;
}

std::shared_ptr<Animation> InitBobbyPlusIdle(void)
{
  std::map<std::string, Bone> bones;
  std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
  std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
  std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 0.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.05f, 0.0f), 500.0));
  positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 1000.0));
  Bone chest("Chest", positions, rotations, scales);
  bones["Chest"] = chest;

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

  std::shared_ptr<Animation> anim =
    std::shared_ptr<Animation>(new Animation("Bobby Plus idle", bones));
  AssetManager::getInstance().addAsset(anim);
  return anim;
}

std::shared_ptr<Animation> InitBobbyPlusBackflip(void)
{
    std::map<std::string, Bone> bones;
    std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
    std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
    std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 000.0));
    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, 0.0f), 200.0));
    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.3f, -0.1f), 400.0));
    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 1.3f, -0.4f), 600.0));
    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 1.5f, -1.0f), 800.0));
    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.9f, -1.5f), 1000.0));
    positions.push_back(VecKeyFrame(mft::vec3(0.0f, 0.0f, -2.2f), 1200.0));

    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.6f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.0f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-2.0f, 0.0f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-3.7f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-4.8f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-5.3f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-6.28f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone chest("Chest", positions, rotations, scales);
    bones["Chest"] = chest;

    // Upper boddy

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.95f, 0.0f, -0.2f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-3.14f, 0.4f, -0.3f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.6f, 0.0f, -0.1f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.6f, 0.0f, -0.08f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.9f, 0.0f, -0.1f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.3f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.6f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));

    Bone upperRightArm("Upper right arm", positions, rotations, scales);
    bones["Upper right arm"] = upperRightArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.17f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -0.2f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.97f, 0.0f, -0.6f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.97f, 0.0f, -0.56f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.1f, 0.0f, -0.3f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.2f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.0f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone lowerRightArm("Lower right arm", positions, rotations, scales);
    bones["Lower right arm"] = lowerRightArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.95f, 0.0f, 0.2f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-3.14f, -0.4f, 0.3f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.1f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.7f, 0.0f, 0.08f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.9f, 0.0f, 0.08f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.3f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.6f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone upperLeftArm("Upper left arm", positions, rotations, scales);
    bones["Upper left arm"] = upperLeftArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.17f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.97f, 0.0f, 0.6f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.97f, 0.0f, 0.56f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.1f, 0.0f, 0.4f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.2f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.0f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone lowerLeftArm("Lower left arm", positions, rotations, scales);
    bones["Lower left arm"] = lowerLeftArm;

    //  Lower boddy

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.1f, 0.0f, 0.15f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.4f, 0.0f, 0.07f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.4f, 0.0f, 0.07f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.5f, 0.0f, 0.07f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.9f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.48f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.4f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone leftThigh("Left thigh", positions, rotations, scales);
    bones["Left thigh"] = leftThigh;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.3f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.35f, 0.0f, 0.07f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-2.3f, 0.0f, 0.07f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-2.3f, 0.0f, 0.07f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.3f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone leftCalf("Left calf", positions, rotations, scales);
    bones["Left calf"] = leftCalf;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.1f, 0.0f, -0.15f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.4f, 0.0f, 0.07f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.6f, 0.0f, -0.07f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.6f, 0.0f, -0.07f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.9f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.48f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(1.4f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone rightThigh("Right thigh", positions, rotations, scales);
    bones["Right thigh"] = rightThigh;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.3f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.35f, 0.0f, 0.07f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-2.3f, 0.0f, 0.07f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-2.3f, 0.0f, 0.07f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-1.3f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.2f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.8f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone rightCalf("Right calf", positions, rotations, scales);
    bones["Right calf"] = rightCalf;
    std::shared_ptr<Animation> anim =
        std::shared_ptr<Animation>(new Animation("Bobby Plus backflip", bones));
    AssetManager::getInstance().addAsset(anim);
    return anim;
}


std::shared_ptr<Animation> InitBobbyPlusDance(void)
{
    std::map<std::string, Bone> bones;
    std::vector<VecKeyFrame> positions = std::vector<VecKeyFrame>();
    std::vector<QuatKeyFrame> rotations = std::vector<QuatKeyFrame>();
    std::vector<VecKeyFrame> scales = std::vector<VecKeyFrame>();

    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.4f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.4f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.4f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.4f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.4f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.4f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.4f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.4f, 0.0f)), 1800.0));
    Bone chest("Chest", positions, rotations, scales);
    bones["Chest"] = chest;

    // Upper boddy

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.6f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.6f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.3f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.3f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.3f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, -0.3f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.6f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.6f, 0.0f)), 1800.0));
    Bone neck("Neck", positions, rotations, scales);
    bones["Neck"] = neck;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -3.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -3.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -1.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.6f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.5f, 0.0f, 0.6f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -1.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -3.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, -3.0f)), 1800.0));
    Bone upperRightArm("Upper right arm", positions, rotations, scales);
    bones["Upper right arm"] = upperRightArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone lowerRightArm("Lower right arm", positions, rotations, scales);
    bones["Lower right arm"] = lowerRightArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.3f)), 1800.0));
    Bone upperLeftArm("Upper left arm", positions, rotations, scales);
    bones["Upper left arm"] = upperLeftArm;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.2f, -0.5f)), 1800.0));
    Bone lowerLeftArm("Lower left arm", positions, rotations, scales);
    bones["Lower left arm"] = lowerLeftArm;

    //  Lower boddy

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.1f, 0.1f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.2f, 0.2f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.2f, 0.2f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.1f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.2f)), 1800.0));
    Bone leftThigh("Left thigh", positions, rotations, scales);
    bones["Left thigh"] = leftThigh;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.25f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.25f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1800.0));
    Bone leftCalf("Left calf", positions, rotations, scales);
    bones["Left calf"] = leftCalf;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(30.0f, 30.0f, 0.0f), AngleDegrees), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(30.0f, 30.0f, 0.0f), AngleDegrees), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(30.0f, 30.0f, 0.0f), AngleDegrees), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(15.0f, 15.0f, 0.0f), AngleDegrees), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f), AngleDegrees), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f), AngleDegrees), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(15.0f, 15.0f, 0.0f), AngleDegrees), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(30.0f, 30.0f, 0.0f), AngleDegrees), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(30.0f, 30.0f, 0.0f), AngleDegrees), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(30.0f, 30.0f, 0.0f), AngleDegrees), 1800.0));
    Bone rightThigh("Right thigh", positions, rotations, scales);
    bones["Right thigh"] = rightThigh;

    positions.clear();
    rotations.clear();
    scales.clear();
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 0.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.25f, 0.0f, 0.0f)), 600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 800.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(0.0f, 0.0f, 0.0f)), 1000.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.25f, 0.0f, 0.0f)), 1200.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 1400.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 1600.0));
    rotations.push_back(QuatKeyFrame(mft::quat::rotate(mft::vec3(-0.5f, 0.0f, 0.0f)), 1800.0));
    Bone rightCalf("Right calf", positions, rotations, scales);
    bones["Right calf"] = rightCalf;
    std::shared_ptr<Animation> anim =
        std::shared_ptr<Animation>(new Animation("Bobby Plus dance", bones));
    AssetManager::getInstance().addAsset(anim);
    return anim;
}
