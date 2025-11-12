#include "Graphics/MatrixStack/MatrixStack.h"
#include "Graphics/Shader/Shader.h"
#include "Globals/Globals.h"

namespace PrakCG {
	MatrixStack Globals::matrixStack = MatrixStack();
	Shader Globals::shader = Shader("res/shaders/object.shader");
}