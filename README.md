# ql-thumbnail

> Generate thumbnail image using OS X Quick Look

Wafer-thin wrapper around the QuickLook `QLThumbnailImageCreate()` API.

## Build

```
$ git clone [...]
cd ql-thumbnail
make
```

## Usage

```
./ql-thumbnail <sourcefile> <destination_thumbnailfile> <type> <width> <height>
./ql-thumbnail image.pdf image.png public.png 1024 1024
./ql-thumbnail sourcecode.cpp thumbnails/sourcecode.png public.jpeg 128 512
```

### Notes

- Size (width/height) values are upper bounds. A smaller thumbnail might be returned.
- Destination folder for output thumbnail image must exist.

### Supported output formats

- "public.jpeg"
- "public.png"
- "com.compuserve.gif"
- "public.jpeg-2000"
- "public.tiff"
- "com.apple.icns"
- "com.adobe.photoshop-image"
- "com.adobe.pdf"
- "com.microsoft.ico"
- "com.microsoft.bmp"
- "com.truevision.tga-image"
- "com.sgi.sgi-image"
- "com.ilm.openexr-image"
- "public.pbm"
- "public.pvr"
- "org.khronos.astc"
- "org.khronos.ktx"
- "com.apple.rjpeg"


## Related

[qlmanage](https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man1/qlmanage.1.html) -- Quick Look Server debug and management tool

## License

MIT © 2016 [Ingve Vormestrand](https://github.com/ingve)
