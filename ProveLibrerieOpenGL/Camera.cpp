#include "Camera.h"

void Camera::setEye(const Vec3f& eye) {
	_eye = eye;
	_isChanged = true;
}
const Vec3f& Camera::getEye() const {
	return _eye;
}

void Camera::setLookAt(const Vec3f& lookat) {
	_lookAt = lookat;
	_isChanged = true;
}

const Vec3f& Camera::getLookAt() const {
	return _lookAt;
}
void Camera::setup(const Vec3f& up) {
	_up = up;
	_isChanged = true;
}
const Vec3f& Camera::getUp() const {
	return _up;
}
void Camera::setFov(const float& fov) {
	_fov = fov;
	_isChanged = true;
	
}
const float Camera::getFov() const {
	return _fov * (180.0 / 3.141592653589793238463);
}
void Camera::setNear(const float& cameraNear) {
	_near = cameraNear;
	_isChanged = true;
}
const float& Camera::getNear() const {
	return _near;
}

void Camera::setFar(const float& cameraFar) {
	_far = cameraFar;
	_isChanged = true;
}
const float& Camera::getFar() const {
	return _far;
}

const float& Camera::getAspectRatio() const {
	return _aspectRatio;
}

void Camera::computeAspectRatio(int width, int height) {
	_aspectRatio = static_cast<double> (width) / static_cast<double> (height);
	_isChanged = true;
}

void Camera::ProcessKeyboard(std::string direction, float deltaTime, std::string scene)
{
    float velocity = 5.5f * deltaTime;
    if (direction == "FORWARD") {
       if (canMove("FORWARD",scene) ) {
           setEye(_eye - (_eye - _lookAt).normalize() * velocity);
           setLookAt(_lookAt - (_eye - _lookAt).normalize() * velocity);
        previousDirection = "FORWARD";
        updateViewMatrix();
        }

    }
    if (direction == "BACKWARD") {
        if (canMove("BACKWARD",scene)) {
            setEye(_eye + (_eye - _lookAt).normalize() * velocity);
            setLookAt(_lookAt + (_eye - _lookAt).normalize() * velocity);
            previousDirection = "BACKWARD";
            updateViewMatrix();

        }


    }
    if (direction == "ROTATION_SX") {
        Vec3f v = (_lookAt - _eye);
        Mat3f rot3 = Mat3f::rotateY(velocity/4 * 3.141592653589793238463 / 8);
        v = rot3 * v;
        _lookAt = v + _eye;
      
        updateViewMatrix();

    }
    if (direction == "ROTATION_DX") {

        Mat3f rot3 = Mat3f::rotateY(velocity/4 * -3.141592653589793238463 / 8);
        Vec3f v = (_lookAt - _eye);      
        v = rot3 * v;
        _lookAt = v + _eye;
      

        updateViewMatrix();

    }
    if (direction == "ROTATION_UP") {
       
        _lookAt.y = _lookAt.y + velocity;

        updateViewMatrix();
    }
    if (direction == "ROTATION_DOWN") {
       

        _lookAt.y = _lookAt.y - velocity;

        updateViewMatrix();
    }
   /* if (direction == "LEFT" || direction == "RIGHT") {
    int sign = walk(direction, scene);
    Vec3f occhio = _eye, vede = _lookAt, asseVerticale = _up;
    Vec3f sguardo = (occhio - vede).normalize();
    Vec3f dir = (sguardo.cross(asseVerticale)).normalize();

    _eye.x = _eye.x + sign* dir.x * velocity;
    _lookAt.x = _lookAt.x + sign* dir.x * velocity;
    _eye.z = _eye.z + sign* dir.z * velocity;
    _lookAt.z = _lookAt.z + sign* dir.z * velocity;
    previousDirection = direction;
    updateViewMatrix();
    }
    */


    if (direction == "LEFT") {
      if (canMove("LEFT", scene)) {
          int sign = 1;
        Vec3f occhio = _eye, vede = _lookAt, asseVerticale = _up;
        Vec3f sguardo = (occhio - vede).normalize();
        
            Vec3f dir = (sguardo.cross(asseVerticale)).normalize();

            _eye.x = _eye.x + dir.x * velocity;
            _lookAt.x = _lookAt.x + dir.x * velocity;

            _eye.z = _eye.z + dir.z * velocity;
            _lookAt.z = _lookAt.z + dir.z * velocity;
            previousDirection = "LEFT";
            updateViewMatrix();
        }

    }
    if (direction == "RIGHT") {
        if (canMove("RIGHT", scene)) {
            int sign = -1;
        Vec3f occhio = _eye, vede = _lookAt, asseVerticale = _up;
        Vec3f sguardo = (occhio - vede).normalize();
        Vec3f dir = (sguardo.cross(asseVerticale)).normalize();
       
            _eye.x = _eye.x - dir.x * velocity;
            _lookAt.x = _lookAt.x - dir.x * velocity;
            _eye.z = _eye.z - dir.z * velocity;
            _lookAt.z = _lookAt.z - dir.z * velocity;
            previousDirection = "RIGHT";
            updateViewMatrix();
        }

    //}
    ///* Vec3f occhio = _eye, vede = _lookAt, asseVerticale = _up;
    //    Vec3f sguardo = (occhio - vede).normalize();
    //    Vec3f dir = (sguardo.cross(asseVerticale)).normalize();

    //        _eye.x = _eye.x - dir.x * velocity;
    //        _lookAt.x = _lookAt.x - dir.x * velocity;
    //        _eye.z = _eye.z - dir.z * velocity;
    //        _lookAt.z = _lookAt.z - dir.z * velocity;
    //        previousDirection = "RIGHT";
    //        updateViewMatrix();*/


}

//int Camera::walk(std::string direction, std::string scene) {
//    int sign;
//    if (direction == "LEFT") {
//        if (canMove("LEFT", scene)) {
//            sign = 1;
//        }
//        }
//        else if (direction == "RIGHT") {
//            if (canMove("RIGHT", scene)) {
//                sign = -1;
//            }
//           return sign;
//        } 
}
bool Camera::canMove(std::string currentDir, std::string scene) {
    bool canMove = false;
    float limit = 30.f;
    //std::cout << "current = " << currentDir << ",  previous = " << previousDir << std::endl;
    if (scene == "stanza") {
        if (fabs(_eye.x) <= limit && fabs(_eye.z) <= limit) { 
            canMove = true; 
        }
        else {
            if (currentDir != previousDirection) {
                if (_eye.x > limit) { 
                    _eye.x = limit;
                }
                else if (_eye.x < -limit) { 
                    _eye.x = -limit; 
                }

                if (_eye.z > limit) { 
                    _eye.z = limit;
                }
                else if (_eye.z < -limit) {
                    _eye.z = -limit; 
                }
                canMove = true;
            }
        }
         return canMove;
    }
    else return true;
}

void Camera::updateProjectionMatrix(){
	float r = _near * tanf(getFov() * 0.5f); // r = n tan (fov/2) e il 2????'
	float t = r / _aspectRatio; // t = aspectRatio * r
	//float h = w / 1.5;
	// 0.78539 è il fov in radianti calcolato su internet
	_projectionMatrix = Mat4f::ProjectionMatrix(r, t, 0, _aspectRatio, _near, _far);
   //_projectionMatrix = Mat4f::ProjectionMatrix(1000,1500, _near, _far);

}

const Mat4f& Camera::getProjectionMatrix() const {
	return _projectionMatrix;
}

const Mat4f& Camera::getViewMatrix() const {
	return _viewMatrix;
}

Mat4f Camera::getCubeMapViewMatrix() const {
	Mat4f mat = _viewMatrix;
	Mat3f temp = mat.getSubmat3x3();
	Mat4f result;
	result = Mat4f::mat4FromMat3(temp);// trasforma in mat3 e poi di nuovo in mat4 in modo da eliminare la parte di rotazione
	
	return result;// trasforma in mat3 e poi di nuovo in mat4 in modo da eliminare la parte di rotazione;
}

void Camera::updateViewMatrix() {
    
	_viewMatrix = Mat4f::ViewMatrix(_eye, _lookAt, _up);
   
}

void Camera::update() {
	if (_isChanged) {
		updateViewMatrix();
		updateProjectionMatrix();

		_isChanged = false;
	}
}
//
//void Camera::Init(int m_windowWidth , int m_windowHeight)
//{
//	Vec3f HTarget(m_target.x, 0.0, m_target.z);
//	HTarget.normalize();
//
//	float Angle = (asin(abs(HTarget.z)))* 3.141592653589793238463/180.0;
//
//	if (HTarget.z >= 0.0f)
//	{
//		if (HTarget.x >= 0.0f)
//		{
//			m_AngleH = 360.0f - Angle;
//		}
//		else
//		{
//			m_AngleH = 180.0f + Angle;
//		}
//	}
//	else
//	{
//		if (HTarget.x >= 0.0f)
//		{
//			m_AngleH = Angle;
//		}
//		else
//		{
//			m_AngleH = 180.0f - Angle;
//		}
//	}
//
//	m_AngleV = -(asin(_lookAt.y)) * 3.141592653589793238463 / 180.0;
//
//	m_OnUpperEdge = false;
//	m_OnLowerEdge = false;
//	m_OnLeftEdge = false;
//	m_OnRightEdge = false;
//	m_mousePos.x = m_windowWidth / 2;
//	m_mousePos.y = m_windowHeight / 2;
//}


