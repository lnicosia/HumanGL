#ifndef _INIT_BOBBY_H_
#define _INIT_BOBBY_H_

#include "Object/GLObject.class.hpp"
#include "Object/Animation.class.hpp"

std::shared_ptr<notrealengine::GLObject>	InitBobby(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyWalking(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyJumping(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyIdle(void);

#endif
