#include <CoreFoundation/CoreFoundation.h>
#include <QuickLook/QuickLook.h>
#include <string>
#include <cassert>
#include <iostream>


class Thumbnail {
public:
	explicit Thumbnail(const std::string& filename);
	void save(const std::string& thumbnail_name,
		const std::string& type, unsigned int width, unsigned int height) const;
private:
	std::string filename_;
};

Thumbnail::Thumbnail(const std::string& filename) {
	assert(filename.size() > 0);
	filename_ = filename;
}

void Thumbnail::save(const std::string& thumbnail_name, const std::string& type,
		unsigned int width, unsigned int height) const {

	CFStringRef type_str_ {nullptr};
	CFStringRef file_str_ {nullptr};
	CFURLRef file_url_ {nullptr};
	CFStringRef thumb_str_ {nullptr};
	CFURLRef thumb_url_ {nullptr};
	CGImageRef image_ {nullptr};
	CGImageDestinationRef thumbnail_ {nullptr};

	CGSize size = CGSizeMake(width, height);

	type_str_ = CFStringCreateWithCString(nullptr, type.c_str(), kCFStringEncodingUTF8);

	file_str_ = CFStringCreateWithCString(nullptr, filename_.c_str(), kCFStringEncodingUTF8);
	file_url_ =  CFURLCreateWithFileSystemPath(nullptr, file_str_, kCFURLPOSIXPathStyle, 0);

	thumb_str_ = CFStringCreateWithCString(nullptr, thumbnail_name.c_str(), kCFStringEncodingUTF8);
	thumb_url_ = CFURLCreateWithFileSystemPath(nullptr, thumb_str_, kCFURLPOSIXPathStyle, 0);

	image_ = QLThumbnailImageCreate(kCFAllocatorDefault, file_url_, size, nullptr);
	if (image_) {
		thumbnail_ = CGImageDestinationCreateWithURL(thumb_url_, type_str_, 1, nullptr);
		CGImageDestinationAddImage(thumbnail_, image_, nullptr);
		CGImageDestinationFinalize(thumbnail_);
	}

	// clean up CoreFoundation gunk
	if (type_str_) CFRelease(type_str_);
	if (file_str_) CFRelease(file_str_);
	if (file_url_) CFRelease(file_url_);
	if (thumb_str_) CFRelease(thumb_str_);
	if (thumb_url_) CFRelease(thumb_url_);
	if (image_) CFRelease(image_);
	if (thumbnail_) CFRelease(thumbnail_);
}

int main(int argc, char *argv[]) {

	if (argc == 6) {
		std::string src {argv[1]};
		std::string dest {argv[2]};
		std::string type {argv[3]};
		std::string width_str {argv[4]};
        unsigned int width = std::stoi(width_str);
		std::string height_str {argv[5]};
        unsigned int height = std::stoi(height_str);
		Thumbnail thumbnail {src};
		thumbnail.save(dest, type, width, height);
	}
	else {
		std::string binary {argv[0]};
		std::cout << "Usage:\n" + binary + " source destination type width height\n";
	}
	return 0;
}
