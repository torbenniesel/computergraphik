#pragma once
#ifndef CHAIN_MANAGER_H
#define CHAIN_MANAGER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Model/Model.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


struct ChainLink {
	glm::vec2 position;
	glm::vec2 rotation;
};

enum ChainElementType {
	CHAIN_ELEMENT_CIRCLE,
	CHAIN_ELEMENT_POINT,
	CHAIN_ELEMENT_RECONNECT_CIRCLE,
	CHAIN_ELEMENT_END_POINT,
};

struct ChainElement {
	ChainElementType type;
	glm::vec2 position;
	float radius = 0;
	bool chooseLeftTangent = true;
	glm::vec2 positionChange = glm::vec2(0);
};

struct TangentPoints {
	glm::vec2 T1; // Tangentenpunkt auf dem ersten Kreis
	glm::vec2 T2; // Tangentenpunkt auf dem zweiten Kreis
};

struct CommonTangent {
	glm::vec2 T1;
	glm::vec2 T2;
	glm::vec2 radialDir;
	float tangentRadient;
};

class ChainManager {
public:
	std::vector<ChainLink> chainLinks;
	std::vector<ChainElement> chainElements;
	float chainLinkLength = 0.22f;
	float chainLinkWidth = 0.1f;

	ChainManager() {
		chainLinks = std::vector<ChainLink>();

		chainLinks = CreateChainLinks();
	}

	void Cleanup();

	void Render();

	void SetWheel(glm::vec2 connectionPoint, float radius, float releaseDegree) {

	}

    glm::vec2 CalculateTangentPoint(glm::vec2 point, glm::vec2 circleCenter, float radius, bool chooseLeftTangent = true) {
        
		glm::vec2 vec_M_to_P = point - circleCenter;
		float dist_M_P = glm::length(vec_M_to_P);
		if (dist_M_P <= radius) { 
			return glm::vec2(std::numeric_limits<float>::quiet_NaN());
		}

		//+/- Radiant at circleCenter to Tangent 1/2 (MP x MT)
		float alpha = acos(radius / dist_M_P);

		//Radiant between x-axis and MP (0-2PI)
		float angle_M_P = atan2(vec_M_to_P.y, vec_M_to_P.x);

		float tangentAngle1 = angle_M_P + alpha; //left from vec_M_to_P, right from point to circleCenter
		float tangentAngle2 = angle_M_P - alpha; //right from vec_M_to_P, left from point to circleCenter

		glm::vec2 tangentPoint1 = circleCenter + glm::vec2(cos(tangentAngle1), sin(tangentAngle1)) * radius;
		glm::vec2 tangentPoint2 = circleCenter + glm::vec2(cos(tangentAngle2), sin(tangentAngle2)) * radius;

		if(chooseLeftTangent) {
			return tangentPoint2;
		} else {
			return tangentPoint1;
		}
	}

	

	CommonTangent CalculateCommonTangent(
		glm::vec2 M1, float R1,
		glm::vec2 M2, float R2,
		bool chooseLeftTangent = true)
	{
		glm::vec2 vec_M1_to_M2 = M2 - M1;
		float d = glm::length(vec_M1_to_M2);

		constexpr float epsilon = 1e-6f;
		if (d <= std::abs(R1 - R2) + epsilon) {
			// Fehlerfall: Gib eine Struktur mit NaN-Vektoren zurück
			glm::vec2 nanVec(std::numeric_limits<float>::quiet_NaN());
			return CommonTangent{ nanVec, nanVec, nanVec };
		}

		float beta = atan2(vec_M1_to_M2.y, vec_M1_to_M2.x);
		float alpha = acos((R1 - R2) / d);

		float theta;
		if (chooseLeftTangent) {
			theta = beta - alpha;
		}
		else {
			theta = beta + alpha;
		}
		float tangentRadient = theta;

		glm::vec2 radialDir = glm::vec2(cos(theta), sin(theta));
		glm::vec2 T1 = M1 + radialDir * R1;
		glm::vec2 T2 = M2 + radialDir * R2;
		glm::vec2 tangentDir = glm::vec2(-radialDir.y, radialDir.x);

		if (glm::dot(T2 - T1, tangentDir) < 0) {
			tangentDir = -tangentDir;
		}

		return CommonTangent{ T1, T2, radialDir, tangentRadient };
	}

	void AddChainElement(ChainElement element) {
		chainElements.push_back(element);
	}

	std::vector<ChainElement> CreateChain() {

		// Create chain with three circle elements
		std::vector<ChainElement> chainElements;

		glm::vec2 M1 = { 4.0f, 0 };
		float R1 = 4.0f;
		glm::vec2 M2 = { 4.0f, 11.0f };
		float R2 = 4.0f;
		ChainElement C1 = { CHAIN_ELEMENT_CIRCLE, M1, R1, true };
		ChainElement C2 = { CHAIN_ELEMENT_CIRCLE, M2, R2, true };
		ChainElement C3 = { CHAIN_ELEMENT_CIRCLE, glm::vec2(8.0f, 2.0f), 1.0f, true};
		ChainElement END = { CHAIN_ELEMENT_RECONNECT_CIRCLE, M1, R1, true };
		
		chainElements.push_back(C1);
		chainElements.push_back(C2);
		chainElements.push_back(C1);

		return chainElements;
	}

	std::vector<ChainLink> CreateChainLinksOnLine(glm::vec2 lineStart, glm::vec2 lineEnd) {
		std::vector<ChainLink> chainLinks;
		
		// Use tangent.T1 and tangent.T2 to position chain links
		float lineLength = glm::length(lineEnd - lineStart);
		int numLinks = static_cast<int>(lineLength / chainLinkLength);
		float residualLength = lineLength - numLinks * chainLinkLength; 
		float offsetPerLink = residualLength / numLinks;
		glm::vec2 linkDirection = glm::normalize(lineEnd - lineStart);

		// Loop for numLinks. Create chain links along the line from lineStart to lineEnd. Offset each link by offsetPerLink
		for (int i = 0; i < numLinks; ++i) {
			glm::vec2 linkPosition = lineStart + linkDirection * (i * (chainLinkLength + offsetPerLink));
			ChainLink link;
			link.position = linkPosition;
			link.rotation = glm::vec2(atan2(linkDirection.y, linkDirection.x), 0.0f); // Store rotation as angle in radians
			chainLinks.push_back(link);

		}

		return chainLinks;
	}

	std::vector<ChainLink> CreateChainLinksAroundCircle(glm::vec2 circlePos, float radius, glm::vec2 startPoint, glm::vec2 endPoint, bool moveClockwise = true, float offsetDegreeRad = 0.0f) {
		std::vector<ChainLink> chainLinks;

		// Calculate angles from circle center to start and end points
		float angleStart = atan2(startPoint.y - circlePos.y, startPoint.x - circlePos.x);
		float angleEnd = atan2(endPoint.y - circlePos.y, endPoint.x - circlePos.x);

		// Calculate the angular difference
		float angleDiff;
		if (moveClockwise) {
			// Clockwise: from angleStart to angleEnd (decreasing angle)
			angleDiff = angleStart - angleEnd;
			if (angleDiff < 0) {
				angleDiff += 2 * M_PI;
			}
		}
		else {
			// Counter-clockwise: from angleStart to angleEnd (increasing angle)
			angleDiff = angleEnd - angleStart;
			if (angleDiff < 0) {
				angleDiff += 2 * M_PI;
			}
		}

		// Apply offset
		angleDiff += offsetDegreeRad;

		// Calculate arc length and number of links
		float arcLength = angleDiff * radius;
		int numLinks = static_cast<int>(arcLength / chainLinkLength);

		if (numLinks <= 0) {
			return chainLinks; // No links to create
		}

		float anglePerLink = angleDiff / numLinks;

		// Create chain links along the arc
		for (int i = 0; i < numLinks; ++i) {
			// Calculate angle for this link (centered in its segment)
			float currentAngle;
			if (moveClockwise) {
				currentAngle = angleStart - anglePerLink * i;
			}
			else {
				currentAngle = angleStart + anglePerLink * i;
			}

			// Calculate position on the circle
			glm::vec2 linkPosition = circlePos + glm::vec2(cos(currentAngle), sin(currentAngle)) * radius;

			// Calculate tangent direction (perpendicular to radius)
			glm::vec2 tangentDirection;
			if (moveClockwise) {
				// Clockwise direction
				tangentDirection = glm::vec2(sin(currentAngle), -cos(currentAngle));
			}
			else {
				// Counter-clockwise direction
				tangentDirection = glm::vec2(-sin(currentAngle), cos(currentAngle));
			}

			ChainLink link;
			link.position = linkPosition;
			link.rotation = glm::vec2(atan2(tangentDirection.y, tangentDirection.x), 0.0f);
			chainLinks.push_back(link);
		}

		return chainLinks;
	}

	

	std::vector<ChainLink> CreateChainLinks() {
		//Loop though chain
		std::vector<ChainLink> chainLinks;

		std::vector<ChainElement> chain = CreateChain();
		CommonTangent tangentC0C1 = CalculateCommonTangent(
			chain[0].position, chain[0].radius,
			chain[1].position, chain[1].radius,
			false
		);

		std::vector<ChainLink> chainLinksBetweenC0C1 = CreateChainLinksOnLine(tangentC0C1.T1, tangentC0C1.T2);
		chainLinks.insert(chainLinks.end(), chainLinksBetweenC0C1.begin(), chainLinksBetweenC0C1.end());

		// Create chain links around second circle
		CommonTangent tangentC1C0 = CalculateCommonTangent(
			chain[1].position, chain[1].radius,
			chain[0].position, chain[0].radius,
			false
		);

		std::vector<ChainLink> chainLinksAroundC1 = CreateChainLinksAroundCircle(chain[1].position, chain[1].radius, tangentC0C1.T2, tangentC1C0.T1, true);
		chainLinks.insert(chainLinks.end(), chainLinksAroundC1.begin(), chainLinksAroundC1.end());

		// Create chain links nextLinkStartPos and first circle
		ChainLink lastLink = chainLinks.back();
		glm::vec2 lastLinkDirection = glm::normalize(lastLink.rotation);
		glm::vec2 nextLinkStartPos = tangentC1C0.T1;// lastLink.position + lastLinkDirection * chainLinkLength;

		std::vector<ChainLink> chainLinksBetweenC1C0 = CreateChainLinksOnLine(nextLinkStartPos, tangentC1C0.T2);
		chainLinks.insert(chainLinks.end(), chainLinksBetweenC1C0.begin(), chainLinksBetweenC1C0.end());

		// Create chain links between second and first circle
		std::vector<ChainLink> chainLinksAroundC0 = CreateChainLinksAroundCircle(chain[0].position, chain[0].radius, tangentC1C0.T2, tangentC0C1.T1, true);
		chainLinks.insert(chainLinks.end(), chainLinksAroundC0.begin(), chainLinksAroundC0.end());

		printf("chainLinksBetweenC0C1 \n");
		for (auto& link : chainLinksBetweenC0C1) {
			
			printf("LINK-C: x = %4.2f y = %4.2f \n", link.position.x, link.position.y);
		}
		printf("chainLinksAroundC1 \n");
		for (auto& link : chainLinksAroundC1) {
			
			printf("LINK-C: x = %4.2f y = %4.2f \n", link.position.x, link.position.y);
		}
		printf("chainLinksBetweenC1C0 \n");
		for (auto& link : chainLinksBetweenC1C0) {
			
			printf("LINK-C: x = %4.2f y = %4.2f \n", link.position.x, link.position.y);
		}
		printf("chainLinksAroundC0 \n");
		for (auto& link : chainLinksAroundC0) {
			
			printf("LINK-C: x = %4.2f y = %4.2f \n", link.position.x, link.position.y);
		}


		return chainLinks;

		//// Radiant between lineEnd and tangent.T1 related to circle center (chain[1].position)
		//float radiusToTangentStart = atan2(tangent2.T1.y - chain[1].position.y, tangent2.T1.x - chain[1].position.x);
		//float radiusToTangentEnd = atan2(tangent2.T2.y - chain[1].position.y, tangent2.T2.x - chain[1].position.x);
		//float angleDiff = radiusToTangentEnd - radiusToTangentStart;
		//if (angleDiff < 0) {
		//	angleDiff += 2 * M_PI;
		//}
		//float circleCircumference = 2 * M_PI * chain[1].radius;
		//float arcLength = angleDiff * chain[1].radius;
		//int numLinksCircle = static_cast<int>(arcLength / chainLinkLength);
		//float anglePerLink = angleDiff / numLinksCircle;
		//
		//// Loop for numLinksCircle. Create chain links along the arc from tangent.T1 to tangent.T2
		//for (int i = 0; i < numLinksCircle; ++i) {
		//	// Calculate angle for this link (centered in its segment)
		//	float currentAngle = radiusToTangentStart + anglePerLink * (i + 0.5f);
		//	
		//	// Calculate position on the circle
		//	glm::vec2 linkPosition = chain[1].position + glm::vec2(cos(currentAngle), sin(currentAngle)) * chain[1].radius;
		//	
		//	// Calculate tangent direction (perpendicular to radius)
		//	glm::vec2 tangentDirection = glm::vec2(-sin(currentAngle), cos(currentAngle));
		//	
		//	ChainLink link;
		//	link.position = linkPosition;
		//	link.rotation = glm::vec2(atan2(tangentDirection.y, tangentDirection.x), 0.0f);
		//	chainLinks.push_back(link);
		//	
		//	printf("CIRCLE LINK: x = %4.2f y = %4.2f angle = %4.2f\n", linkPosition.x, linkPosition.y, currentAngle*180/M_PI);
		//}

		//

		//return chainLinks;

		//for(ChainElement element: chain) {
		//	switch (element.type) {
		//	case CHAIN_ELEMENT_CIRCLE:
		//		// Create chain links around circle
		//		break;
		//	case CHAIN_ELEMENT_POINT:
		//		// Create chain links to point
		//		break;
		//	case CHAIN_ELEMENT_RECONNECT_CIRCLE:
		//		// Reconnect to first circle
		//		break;
		//	case CHAIN_ELEMENT_END_POINT:
		//		// End chain
		//		break;
		//	default:
		//		break;
		//	}
		//}

		//for (auto it = chain.begin(); it != chain.end(); ++it) {
		//	int index = std::distance(chain.begin(), it);

		//	if (it->type == CHAIN_ELEMENT_CIRCLE) {
		//		ChainElement currentCircle = *it;
		//		ChainElement nextElement;
		//		if (index + 1 < chain.size()) {
		//			nextElement = chain[index + 1];
		//		} else {
		//			break; // No next element
		//		}
		//		if (nextElement.type == CHAIN_ELEMENT_CIRCLE) {
		//			// Calculate common tangent between two circles
		//			CommonTangent tangent = CalculateCommonTangent(
		//				currentCircle.position, currentCircle.radius,
		//				nextElement.position, nextElement.radius,
		//				currentCircle.chooseLeftTangent
		//			);
		//			// Use tangent.T1 and tangent.T2 to position chain links
		//			// along the tangent line between the two circles
		//		}
		//		else if (nextElement.type == CHAIN_ELEMENT_POINT) {
		//			// Calculate tangent point from circle to point
		//			glm::vec2 tangentPoint = CalculateTangentPoint(
		//				nextElement.position,
		//				currentCircle.position,
		//				currentCircle.radius,
		//				currentCircle.chooseLeftTangent
		//			);
		//			// Use tangentPoint to position chain links
		//			// from the circle to the point
		//		}
		//	}
		//}

	}
};
#endif

