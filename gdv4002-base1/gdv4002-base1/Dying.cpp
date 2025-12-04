#include "Engine.h"
#include "Dying.h"
#include "GameObject2D.h"
#include "Lives.h"

Dying::Dying(glm::vec3 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID) {
	Texture = initTextureID;
	active = false;
	
}

void Dying::render() {
	if (!active) return; // only render while active
	glPushMatrix();

	// Move to object's position
	glTranslatef(position.x, position.y, position.z);


	float pivotY = -0.5f * size.y;
	// Translate to pivot, rotate, then translate back so rotation occurs about the bottom center
	glTranslatef(0.0f, pivotY, 0.0f);
	glRotatef(glm::degrees(orientation), 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -pivotY, 0.0f);

	// Apply scaling
	glScalef(size.x, size.y, 1.0f);

	if (textureID > 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(1.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	glEnd();

	if (textureID > 0) {
		glDisable(GL_TEXTURE_2D);
	}

	glPopMatrix();
}



void Dying::update(double tDelta) {
	if (!active) return;

	float rotateAmount = glm::radians(90.0f) * (float)tDelta * rotateSign;
	orientation += rotateAmount;

	// When rotation goes beyond threshold remove object and corresponding life
	if (rotateSign > 0.0f) {
		if (orientation >= 1.4f) {
			// remove matching Lives object at same position
			for (Lives* L : Lives::lives) {
				if (!L) continue;
				if (L->position == this->position) {
					deleteObject(L);
					break;
				}
			}
			deleteObject(this);
		}
	} else {
		if (orientation <= -1.4f) {
			for (Lives* L : Lives::lives) {
				if (!L) continue;
				if (L->position == this->position) {
					deleteObject(L);
					break;
				}
			}
			deleteObject(this);
		}
	}
}

void Dying::start() {
	active = true;
	GLuint leftTex = loadTexture("Resources\\Textures\\Dyingleft.png");
	GLuint rightTex = loadTexture("Resources\\Textures\\DyingRight.png");
	if (textureID == leftTex) rotateSign = 1.0f;
	else if (textureID == rightTex) rotateSign = -1.0f;
	else rotateSign = 1.0f; // default
}