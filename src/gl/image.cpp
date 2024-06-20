#include "gl/image.hpp"
#include "lib/stb_image.hpp"

using namespace std;
using namespace huigl;

void Image::setImage(unsigned char *data, const unsigned int &width,
                     const unsigned int &height) {
  this->data = data;
  this->width = width;
  this->height = height;
}

shared_ptr<Image> Image::fromFile(const char *path) {
  int width, height, channels;
  return make_shared<Image>(stbi_load(path, &width, &height, &channels, 0),
                            width, height);
}

Image::Image(unsigned char *data, unsigned int width, unsigned int height) {
  this->setImage(data, width, height);
}

// Image::Image(Image &&image) {
//   this->data = image.data;
//   this->width = image.width;
//   this->height = image.height;
//   image.data = nullptr;
//   image.width = 0;
//   image.height = 0;
// }

Image::~Image() { stbi_image_free(this->data); }
