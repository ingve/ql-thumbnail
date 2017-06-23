#include <CoreFoundation/CoreFoundation.h>
#include <QuickLook/QuickLook.h>
#include <string>
#include <cassert>
#include <iostream>

class Thumbnail {
public:
  explicit Thumbnail(const std::string& filename);
  bool save(const std::string& thumbnail_name, const std::string& type, unsigned int width, unsigned int height, float compression_quality = 1.0f) const;
private:
  std::string filename_;
};

Thumbnail::Thumbnail(const std::string& filename) {
  assert(filename.size() > 0);
  filename_ = filename;
}

bool Thumbnail::save(const std::string& thumbnail_name, const std::string& type, unsigned int width, unsigned int height, float compression_quality) const {
  bool res {false};
  CFStringRef type_str_ {nullptr};
  CFStringRef file_str_ {nullptr};
  CFURLRef file_url_ {nullptr};
  CFStringRef thumb_str_ {nullptr};
  CFURLRef thumb_url_ {nullptr};
  CGImageRef image_ {nullptr};
  CGImageDestinationRef thumbnail_ {nullptr};
  CFDictionaryRef properties_ {nullptr};
  CFStringRef property_names[1];
  CFTypeRef property_values[1];
  property_names[0] = kCGImageDestinationLossyCompressionQuality;
  property_values[0] = CFNumberCreate(nullptr, kCFNumberFloatType, &compression_quality);
  properties_ = CFDictionaryCreate(nullptr, (const void **)property_names, (const void **)property_values, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

  CGSize size = CGSizeMake(width, height);

  type_str_ = CFStringCreateWithCString(nullptr, type.c_str(), kCFStringEncodingUTF8);

  file_str_ = CFStringCreateWithCString(nullptr, filename_.c_str(), kCFStringEncodingUTF8);
  file_url_ =  CFURLCreateWithFileSystemPath(nullptr, file_str_, kCFURLPOSIXPathStyle, 0);

  thumb_str_ = CFStringCreateWithCString(nullptr, thumbnail_name.c_str(), kCFStringEncodingUTF8);
  thumb_url_ = CFURLCreateWithFileSystemPath(nullptr, thumb_str_, kCFURLPOSIXPathStyle, 0);

  image_ = QLThumbnailImageCreate(kCFAllocatorDefault, file_url_, size, nullptr);
  if (image_) {
    thumbnail_ = CGImageDestinationCreateWithURL(thumb_url_, type_str_, 1, nullptr);
    if (thumbnail_) {
      CGImageDestinationAddImage(thumbnail_, image_, properties_);
      res = CGImageDestinationFinalize(thumbnail_);
    }
  }

  // clean up CoreFoundation gunk
  if (type_str_) CFRelease(type_str_);
  if (file_str_) CFRelease(file_str_);
  if (file_url_) CFRelease(file_url_);
  if (thumb_str_) CFRelease(thumb_str_);
  if (thumb_url_) CFRelease(thumb_url_);
  if (image_) CFRelease(image_);
  if (thumbnail_) CFRelease(thumbnail_);
  if (properties_) CFRelease(properties_);
  if (property_values[0]) CFRelease(property_values[0]);
  return res;
}

int main(int argc, char *argv[]) {

  if (argc >= 6) {
    std::string src {argv[1]};
    std::string dest {argv[2]};
    std::string type {argv[3]};
    std::string width_str {argv[4]};
    unsigned int width = std::stoi(width_str);
    std::string height_str {argv[5]};
    unsigned int height = std::stoi(height_str);
    Thumbnail thumbnail {src};
    float quality = (argc == 7) ? std::stof(argv[6]) : 1.0f;
    bool res = thumbnail.save(dest, type, width, height, quality);
    if (!res) {
      std::cerr << "Error generating thumbnail" << std::endl;
    }
  }
  else {
    std::string binary {argv[0]};
    std::cout << "Usage:\n" + binary + " source destination type width height [quality]" << std::endl;
  }
  return 0;
}
