#include "Plugin.h"
#include "imgui/imgui.h"

namespace PrakCG {

	// Menu
	MenuEntries::MenuEntries(Plugin*& currentPlugin)
		: currentPlugin(currentPlugin) {

	}

	void MenuEntries::OnImGuiRender() {
		for (auto& test : plugins) {
			if (ImGui::Button(test.first.c_str())) {
				currentPlugin = test.second();
			}
		}
	}

}