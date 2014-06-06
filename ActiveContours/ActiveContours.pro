#-------------------------------------------------
#
# Project created by QtCreator 2014-06-07T00:31:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActiveContours
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    image_processing/algorithms/active_contour.cpp \
    image_processing/algorithms/edge_based_active_contour.cpp \
    image_processing/algorithms/filters.cpp \
    image_processing/algorithms/hausdorff_distance.cpp \
    image_processing/algorithms/region_based_active_contour.cpp \
    image_processing/algorithms/region_based_active_contour_yuv.cpp \
    image_processing/algorithms/tracking_active_contour.cpp

HEADERS  += mainwindow.h \
    image_processing/algorithms/active_contour.hpp \
    image_processing/algorithms/edge_based_active_contour.hpp \
    image_processing/algorithms/filters.hpp \
    image_processing/algorithms/hausdorff_distance.hpp \
    image_processing/algorithms/region_based_active_contour.hpp \
    image_processing/algorithms/region_based_active_contour_yuv.hpp \
    image_processing/algorithms/tracking_active_contour.hpp \
    image_processing/data_structures/list.hpp \
    image_processing/data_structures/matrix.hpp

INCLUDEPATH += image_processing/data_structures \
               image_processing/algorithms

FORMS    += mainwindow.ui
