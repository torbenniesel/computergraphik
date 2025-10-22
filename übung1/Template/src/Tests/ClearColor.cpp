#include <GL/glew.h>
#include "Tests/ClearColor.h"
#include "imgui/imgui.h"

namespace PrakCG {
	TestClearColor::TestClearColor() :
		width(0), 
		height(0),
		clearColor{ 0.2f, 0.3f, 0.8f, 1.0f },
		showComplementaryColor(false)//,
		//complementaryColor{ 0, 0, 0, 1.0f }
	{
	}

	TestClearColor::~TestClearColor() {

	}

	bool IsValid(float value) {
		if (0.0f > value) return false;
		if (1.0f < value) return false;
		return true;
	}

	void TestClearColor::OnUpdate(double deltaTime) {

	}

	void TestClearColor::OnRender() {

		if (false == showComplementaryColor) {
			assert(IsValid(clearColor[0]) && IsValid(clearColor[1]) && IsValid(clearColor[2]) && IsValid(clearColor[3]));
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		}
		else {
			for (int i = 0; i < 3; i++)
				complementaryColor[i] = 1.0f - clearColor[i];

			assert(IsValid(complementaryColor[0]) && IsValid(complementaryColor[1]) && IsValid(complementaryColor[2]) && IsValid(complementaryColor[3]));
			glClearColor(complementaryColor[0], complementaryColor[1], complementaryColor[2], complementaryColor[3]);
		}
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void TestClearColor::OnImGuiRender() {
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::ColorEdit4("Clear Color", clearColor);
		ImGui::NewLine();
		ImGui::Checkbox("Draw complementary color?", &showComplementaryColor);
	}

	// Framebuffer hook: called when framebuffer / window size has changed
	void TestClearColor::OnFrameBufferChanged(unsigned int width, unsigned int height) {
		this->width = width; 
		this->height = height;
	}
}