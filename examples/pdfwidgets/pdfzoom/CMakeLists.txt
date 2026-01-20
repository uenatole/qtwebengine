# Copyright (C) 2026 Aliaksei Krayov <uenatole@gmail.com>
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(pdfviewer LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/pdfwidgets/pdfzoom")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PdfWidgets)

qt_add_executable(pdfzoom
        main.cpp
)

set_target_properties(pdfzoom PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
)

target_link_libraries(pdfzoom PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::PdfWidgets
)

install(TARGETS pdfzoom
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
