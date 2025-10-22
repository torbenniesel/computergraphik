#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace PrakCG {
	/// <summary>
	/// Abstract base class for a plugin, e.g. code base for a lesson
	/// </summary>
	class Plugin {
	public:
		/// <summary>
		/// Prepare the model
		///		- init the variables
		///		- load models
		///		- load textures
		/// </summary>
		Plugin() {};

		/// <summary>
		/// Default destructor
		/// </summary>
		virtual ~Plugin() {};

		/// <summary>
		/// Update the model:
		///		- evaluation of the interaction
		///		- simulation logic 
		/// </summary>
		/// <param name="deltaTime">time duration of the last frame in ms</param>
		virtual void OnUpdate(double deltaTime) {}

		/// <summary>
		/// Render the model: 
		///		- specify the camera
		///		- specify the lights
		///		- render the scene / objects
		/// </summary>
		virtual void OnRender() {}

		/// <summary>
		/// Specification of the GUI elements, use ImGui functionionality 
		/// </summary>
		virtual void OnImGuiRender() {}

		/// <summary>
		/// Call when window was resized
		/// </summary>
		/// <param name="width">framebuffer dimension in x</param>
		/// <param name="height">framebuffer dimension in y</param>
		virtual void OnFrameBufferChanged(unsigned int width, unsigned int height) {}
	};

	/// <summary>
	/// Management of the main menu entries 
	/// </summary>
	class MenuEntries : public Plugin {
	public:
		MenuEntries(Plugin*& currentPluginPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterPlugin(const std::string& name) {
			std::cout << "Registering plugin " << name << std::endl;
			plugins.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Plugin*& currentPlugin;
		std::vector<std::pair<std::string, std::function<Plugin* ()>>> plugins;

	};

}