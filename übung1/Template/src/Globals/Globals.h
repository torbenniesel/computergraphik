#pragma once

#include "Graphics/MatrixStack/MatrixStack.h"
#include "Graphics/Shader/Shader.h"

namespace PrakCG {

	class Globals {
	public:
		static MatrixStack matrixStack;	// common matrix stack
		static Shader shader;			// common shader for all models
	};
}