#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/fl_draw.H>

#include <map>
#include <string>
#include <vector>

namespace gooey::fltk::impl {

    class FLTKBackgroundImageCollection {
        std::vector<std::string>                   _imageNamesInOrder;
        std::map<std::string, Fl_Shared_Image*>    _originalImages;
        std::map<std::string, Fl_Shared_Image*>    _currentImages;
        std::map<std::string, std::pair<int, int>> _currentImageSizes;

    public:
        bool AddImage(const std::string& imagePath) {
            if (_originalImages.find(imagePath) == _originalImages.end()) {
                auto* image = Fl_Shared_Image::get(imagePath.c_str());
                if (image) {
                    _imageNamesInOrder.push_back(imagePath);
                    _originalImages[imagePath]    = image;
                    _currentImages[imagePath]     = image;
                    _currentImageSizes[imagePath] = std::make_pair(image->w(), image->h());
                } else return false;
            }
            return true;
        }

        bool RemoveImage(const std::string& imagePath) {
            if (_originalImages.find(imagePath) != _originalImages.end()) {
                auto* image = _originalImages[imagePath];
                if (image) {
                    image->release();
                    _originalImages.erase(imagePath);
                    _currentImages.erase(imagePath);
                    _currentImageSizes.erase(imagePath);
                    _imageNamesInOrder.erase(
                        std::find(_imageNamesInOrder.begin(), _imageNamesInOrder.end(), imagePath)
                    );
                    return true;
                }
            }
            return false;
        }

        bool ResizeImage(const std::string& imagePath, int width, int height) {
            auto* newImage = Fl_Shared_Image::get(imagePath.c_str(), width, height);
            if (newImage) {
                _currentImages[imagePath]->release();
                _currentImages[imagePath]     = newImage;
                _currentImageSizes[imagePath] = std::make_pair(width, height);
                return true;
            }
            return false;
        }

        bool DrawSingle(const std::string& imagePath, int x, int y, int width, int height) {
            if (auto currentImageSize = _currentImageSizes.find(imagePath);
                currentImageSize != _currentImageSizes.end()) {
                if (currentImageSize->second.first != width ||
                    currentImageSize->second.second != height) {
                    if (!ResizeImage(imagePath, width, height)) return false;
                }
                fl_push_clip(x, y, width, height);
                _currentImages[imagePath]->draw(0, 0, width, height, 0, 0);  // 2 extra on 1.3.8 ...
                fl_pop_clip();
            }
            return false;
        }

        void DrawAll(int x, int y, int width, int height) {
            for (auto& imagePath : _imageNamesInOrder) DrawSingle(imagePath, x, y, width, height);
        }
    };
}