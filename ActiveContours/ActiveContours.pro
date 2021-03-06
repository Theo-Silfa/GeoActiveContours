#-------------------------------------------------
#
# Project created by QtCreator 2014-06-07T00:31:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActiveContours
TEMPLATE = app

DEFINES += "HAS_8_CONNEXITY=false"

SOURCES += image_processing/algorithms/active_contour.cpp \
    image_processing/algorithms/edge_based_active_contour.cpp \
    image_processing/algorithms/filters.cpp \
    image_processing/algorithms/hausdorff_distance.cpp \
    image_processing/algorithms/region_based_active_contour.cpp \
    image_processing/algorithms/region_based_active_contour_yuv.cpp \
    image_processing/algorithms/tracking_active_contour.cpp \
    UI/src/main.cpp \
    UI/src/mainwindow.cpp \
    UI/src/smartqgraphicsscene.cpp \
    UI/src/smartqgraphicsview.cpp \
    UI/src/tooldialog.cpp

HEADERS  += image_processing/algorithms/active_contour.hpp \
    image_processing/algorithms/edge_based_active_contour.hpp \
    image_processing/algorithms/filters.hpp \
    image_processing/algorithms/hausdorff_distance.hpp \
    image_processing/algorithms/region_based_active_contour.hpp \
    image_processing/algorithms/region_based_active_contour_yuv.hpp \
    image_processing/algorithms/tracking_active_contour.hpp \
    image_processing/data_structures/list.hpp \
    image_processing/data_structures/matrix.hpp \
    UI/src/mainwindow.h \
    UI/src/smartqgraphicsscene.h \
    UI/src/smartqgraphicsview.h \
    UI/src/tooldialog.h

INCLUDEPATH += image_processing/data_structures \
               image_processing/algorithms

FORMS    += UI/forms/mainwindow.ui \
    UI/forms/tooldialog.ui

CONFIG(debug, debug|release) {
    CONFIG += console
}
