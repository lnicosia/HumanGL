#ifndef _UI_H_
#define _UI_H_

/**	Init all the UI
*/
void InitUI( void );

/**	Update the model pannel hierarchical view with the current object
*/
void UpdateModelPannel( void );

/**	Update the transform pannel printed data
*/
void UpdateTransformPannel( void );

/**	Update the color pannel printed data
*/
void UpdateColorPannel( void );

/**	Select mesh
*/
void SelectMesh(std::shared_ptr<Mesh> mesh);

/**	Swap between wireframe and fill modes
*/
void ChangeDrawMode( void );

/**	Swap between lit and unlit modes
*/
void ChangeLightingMode( void );

/**	Enable/Disable grid
*/
void DrawGrid( void );

/**	Enable/Disable Cubemap
*/
void DrawCubemap( void );

/**	Render model
*/
void RenderModel( void );

/**	Render Bobby
*/
void RenderBobby( void );

/**	Populate the printable armature from the currently selected object
*/
void PopulateArmature( void );

/**	Print the full armature
*/
void PrintFullArmature( void );

/**	Update the animation pannel
*/
void UpdateAnimationPannel( void );

/**	Init the top pannel
*/
void InitTopPannel( void );

/**	Init the scene pannel
*/
void InitScenePannel( void );

/**	Init the model pannel
*/
void InitModelPannel( void );

/**	Init the transform pannel
*/
void InitTransformPannel( void );

/**	Init the animation list pannel
*/
void InitAnimationListPannel( void );

/**	Init the animation pannel
*/
void InitAnimationPannel( void );

/**	Play the currently selecetd animation on the currently selected object
*/
void PlayAnimation( void );

/**	Pause the currently selecetd animation on the currently selected object
*/
void PauseAnimation( void );

/**	Reset object pose and stop its animation
*/
void ResetObjectPose( void );

/**	Update animation speed text in animation control pannel
*/
void UpdateAnimationSpeedText( void );

/**	Update animation list
*/
void UpdateAnimationList( void );

/**	Update animation time text
*/
void UpdateAnimationTimeText( void );

/**	Update animation status text
*/
void UpdateAnimationStatusText( void );

#endif // !_UI_H_
