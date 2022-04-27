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

#endif // !_UI_H_
