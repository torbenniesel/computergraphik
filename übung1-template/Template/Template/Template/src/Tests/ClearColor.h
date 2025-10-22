#pragma once
#include "Plugins/Plugin.h"

namespace PrakCG {

	/// <summary>
	/// A simple test to use the GUI to select the background color
	/// </summary>
	class TestClearColor : public Plugin {

	public:
		TestClearColor();
		~TestClearColor();

		/// <summary>
		/// Nothing to do here
		/// </summary>
		/// <param name="deltaTime"></param>
		void OnUpdate(double deltaTime) override;

		/// <summary>
		/// Render the test scene 
		/// </summary>
		void OnRender() override;

		/// <summary>
		/// Specification of the GUI elements, ImGui color selector
		/// </summary>
		void OnImGuiRender() override;

		/// <summary>
		/// Call when window was resized
		/// </summary>
		/// <param name="width">framebuffer dimension in x</param>
		/// <param name="height">framebuffer dimension in y</param>
		void OnFrameBufferChanged(unsigned int width, unsigned int height) override;

	private:
		int width;
		int height;

		float clearColor[4];
		bool showComplementaryColor;
		float complementaryColor[4];
	};
}

