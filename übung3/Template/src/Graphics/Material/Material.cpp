#include "Material.h"

// data obtained from http://devernay.free.fr/cours/opengl/materials.html
// hint: for the use in OpenGL multiply the shininess by 128!

/*
    static instances of common materials
*/

Material Material::emerald = { glm::vec4(0.0215, 0.1745, 0.0215, 1.0f), glm::vec4(0.07568, 0.61424, 0.07568, 1.0f), glm::vec4(0.633, 0.727811, 0.633, 1.0f), glm::vec4(0,0,0,1.0f), 0.6f};
Material Material::jade = { glm::vec4(0.135, 0.2225, 0.1575, 1.0f), glm::vec4(0.54, 0.89, 0.63, 1.0f), glm::vec4(0.316228, 0.316228, 0.316228, 1.0f), glm::vec4(0,0,0,1.0f), 0.1f };
Material Material::obsidian = { glm::vec4(0.05375, 0.05, 0.06625, 1.0f), glm::vec4(0.18275, 0.17, 0.22525, 1.0f), glm::vec4(0.332741, 0.328634, 0.346435, 1.0f), glm::vec4(0,0,0,1.0f), 0.3f };
Material Material::pearl = { glm::vec4(0.25, 0.20725, 0.20725, 1.0f), glm::vec4(1, 0.829, 0.829, 1.0f), glm::vec4(0.296648, 0.296648, 0.296648, 1.0f), glm::vec4(0,0,0,1.0f), 0.088f };
Material Material::ruby = { glm::vec4(0.1745, 0.01175, 0.01175, 1.0f), glm::vec4(0.61424, 0.04136, 0.04136, 1.0f), glm::vec4(0.727811, 0.626959, 0.626959, 1.0f), glm::vec4(0,0,0,1.0f), 0.6f };
Material Material::turquoise = { glm::vec4(0.1, 0.18725, 0.1745, 1.0f), glm::vec4(0.396, 0.74151, 0.69102, 1.0f), glm::vec4(0.297254, 0.30829, 0.306678, 1.0f), glm::vec4(0,0,0,1.0f), 0.1f };
Material Material::brass = { glm::vec4(0.329412, 0.223529, 0.027451, 1.0f), glm::vec4(0.780392, 0.568627, 0.113725, 1.0f), glm::vec4(0.992157, 0.941176, 0.807843, 1.0f), glm::vec4(0,0,0,1.0f), 0.21794872f };
Material Material::bronze = { glm::vec4(0.2125, 0.1275, 0.054, 1.0f), glm::vec4(0.714, 0.4284, 0.18144, 1.0f), glm::vec4(0.393548, 0.271906, 0.166721, 1.0f), glm::vec4(0,0,0,1.0f), 0.2f };
Material Material::chrome = { glm::vec4(0.25, 0.25, 0.25, 1.0f), glm::vec4(0.4, 0.4, 0.4, 1.0f), glm::vec4(0.774597, 0.774597, 0.774597, 1.0f), glm::vec4(0,0,0,1.0f), 0.6f };
Material Material::copper = { glm::vec4(0.19125, 0.0735, 0.0225, 1.0f), glm::vec4(0.7038, 0.27048, 0.0828, 1.0f), glm::vec4(0.256777, 0.137622, 0.086014, 1.0f), glm::vec4(0,0,0,1.0f), 0.1f };
Material Material::gold = { glm::vec4(0.24725, 0.1995, 0.0745, 1.0f), glm::vec4(0.75164, 0.60648, 0.22648, 1.0f), glm::vec4(0.628281, 0.555802, 0.366065, 1.0f), glm::vec4(0,0,0,1.0f), 0.4f };
Material Material::silver = { glm::vec4(0.19225, 0.19225, 0.19225, 1.0f), glm::vec4(0.50754, 0.50754, 0.50754, 1.0f), glm::vec4(0.508273, 0.508273, 0.508273, 1.0f), glm::vec4(0,0,0,1.0f), 0.4f };
Material Material::black_plastic = { glm::vec4(0.01, 0.01, 0.01, 1.0f), glm::vec4(0.01, 0.01, 0.01, 1.0f), glm::vec4(0.50, 0.50, 0.50, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::red_plastic = { glm::vec4(0.1, 0.0, 0.0, 1.0f), glm::vec4(0.5, 0.0, 0.0, 1.0f), glm::vec4(0.7, 0.6, 0.6, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::green_plastic = { glm::vec4(0.05, 0.1, 0.05, 1.0f), glm::vec4(0.1, 0.35, 0.1, 1.0f), glm::vec4(0.45, 0.55, 0.45, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::blue_plastic = { glm::vec4(0.05, 0.05, 0.1, 1.0f), glm::vec4(0.1, 0.1, 0.35, 1.0f), glm::vec4(0.45, 0.55, 0.45, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::cyan_plastic = { glm::vec4(0.05, 0.1, 0.06, 1.0f), glm::vec4(0.1, 0.50980392, 0.50980392, 1.0f), glm::vec4(0.50196078, 0.50196078, 0.50196078, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::magenta_plastic = { glm::vec4(0.1, 0.05, 0.1, 1.0f), glm::vec4(0.50980392, 0.0f, 0.50980392, 1.0f), glm::vec4(0.50196078, 0.50196078, 0.50196078, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::yellow_plastic = { glm::vec4(0.1, 0.1, 0.05, 1.0f), glm::vec4(0.5, 0.5, 0.0, 1.0f), glm::vec4(0.60, 0.60, 0.50, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::white_plastic = { glm::vec4(0.1, 0.1, 0.1, 1.0f), glm::vec4(0.55, 0.55, 0.55, 1.0f), glm::vec4(0.70, 0.70, 0.70, 1.0f), glm::vec4(0,0,0,1.0f), .25f };
Material Material::black_rubber = { glm::vec4(0.02, 0.02, 0.02, 1.0f), glm::vec4(0.01, 0.01, 0.01, 1.0f), glm::vec4(0.4, 0.4, 0.4, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };
Material Material::cyan_rubber = { glm::vec4(0.05, 0.1, 0.1, 1.0f), glm::vec4(0.4, 0.5, 0.5, 1.0f), glm::vec4(0.04, 0.7, 0.7, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };
Material Material::green_rubber = { glm::vec4(0.05, 0.1, 0.05, 1.0f), glm::vec4(0.4, 0.5, 0.4, 1.0f), glm::vec4(0.04, 0.7, 0.04, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };
Material Material::red_rubber = { glm::vec4(0.1, 0.05, 0.05, 1.0f), glm::vec4(0.5, 0.4, 0.4, 1.0f), glm::vec4(0.7, 0.04, 0.04, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };
Material Material::white_rubber = { glm::vec4(0.1, 0.1, 0.1, 1.0f), glm::vec4(0.5, 0.5, 0.5, 1.0f), glm::vec4(0.7, 0.7, 0.7, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };
Material Material::yellow_rubber = { glm::vec4(0.1, 0.1, 0.05, 1.0f), glm::vec4(0.5, 0.5, 0.4, 1.0f), glm::vec4(0.7, 0.7, 0.04, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };
Material Material::grey_rubber = { glm::vec4(0.1, 0.1, 0.1, 1.0f), glm::vec4(0.2, 0.2, 0.2, 1.0f), glm::vec4(0.3, 0.3, 0.3, 1.0f), glm::vec4(0,0,0,1.0f), .078125f };

// function to mix two materials with a proportion
Material Material::mix(Material m1, Material m2, float mix) {
    if (mix < 0) {
        return m2;
    }
    else if (mix > 1) {
        return m1;
    }
    return {
        // set lighting values based on proportion
        m1.ambient * mix + m2.ambient * (1 - mix),
        m1.diffuse * mix + m2.diffuse * (1 - mix),
        m1.specular * mix + m2.specular * (1 - mix),
        m1.emission * mix + m2.emission * (1 - mix),
        m1.shininess * mix + m2.shininess * (1 - mix)
    };
}

aiColor4D Color::white = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
aiColor4D Color::gray = aiColor4D(0.5f, 0.5f, 0.5f, 1.0f);
aiColor4D Color::black = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
aiColor4D Color::red = aiColor4D(1.0f, 0.0f, 0.0f, 1.0f);
aiColor4D Color::green = aiColor4D(0.0f, 1.0f, 0.0f, 1.0f);
aiColor4D Color::blue = aiColor4D(0.0f, 0.0f, 1.0f, 1.0f); 
aiColor4D Color::lightblue = aiColor4D(0.0f, 1.0f, 1.0f, 1.0f);

aiColor4D Color::maroon = aiColor4D(0.9803f, 0.7451f, 0.8314f, 1.0f);
aiColor4D Color::pink = aiColor4D(0.6667f, 0.4314f, 0.1569f, 1.0f);
aiColor4D Color::brown = aiColor4D(0.9608f, 0.4314f, 0.1569f, 1.0f);
aiColor4D Color::orange = aiColor4D(0.9608f, 0.5098f, 0.1882f, 1.0f);
aiColor4D Color::apricot = aiColor4D(1.0f, 0.8431f, 0.7059f, 1.0f);
aiColor4D Color::olive = aiColor4D(0.0f, 0.5f, 0.5f, 1.0f);
aiColor4D Color::beige = aiColor4D(1.0f, 0.9804f, 0.7843f, 1.0f);
aiColor4D Color::lime = aiColor4D(0.8235f, 0.9608f, 0.2352f, 1.0f);
aiColor4D Color::mint = aiColor4D(0.6667f, 1.0f, 0.7647f, 1.0f);
aiColor4D Color::teal = aiColor4D(0.0f, 0.5f, 0.5f, 1.0f);
aiColor4D Color::cyan = aiColor4D(0.2745f, 0.9412f, 0.9412f, 1.0f);
aiColor4D Color::purple = aiColor4D(0.5686f, 0.1176f, 0.7059f, 1.0f);
aiColor4D Color::lavender = aiColor4D(0.8627f, 0.7451f, 1.0f, 1.0f);
aiColor4D Color::magenta = aiColor4D(0.9412f, 0.1961f, 0.9020f, 1.0f);
aiColor4D Color::yellow = aiColor4D(1.0f, 1.0f, 0.0f, 1.0f);

aiColor4D Color::mix(aiColor4D c1, aiColor4D c2, float mix)
{
    if (mix < 0) {
        return c2;
    }
    else if (mix > 1) {
        return c1;
    }
    return aiColor4D(c1 * mix + c2 * (1 - mix));
}
