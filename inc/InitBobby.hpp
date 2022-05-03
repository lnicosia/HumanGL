#ifndef _INIT_BOBBY_H_
#define _INIT_BOBBY_H_

#include "Object/GLObject.class.hpp"
#include "Object/Animation.class.hpp"

std::shared_ptr<notrealengine::GLObject>	InitBobby(void);
std::shared_ptr<notrealengine::GLObject>	InitRoundy(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyWalking(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyJumping(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyIdle(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyBackflip(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyDance(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyMuayThai(void);

std::shared_ptr<notrealengine::GLObject>	InitBobbyPlus(void);
std::shared_ptr<notrealengine::GLObject>	InitRoundyPlus(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyPlusWalking(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyPlusJumping(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyPlusIdle(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyPlusBackflip(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyPlusDance(void);
std::shared_ptr<notrealengine::Animation>	InitBobbyPlusMuayThai(void);

#endif
