QT += core widgets

TARGET = Biblioteca
TEMPLATE = app

# Configurazione delle directory di output
DESTDIR = $$PWD                    # Eseguibile nella root del progetto
OBJECTS_DIR = $$PWD/build/obj      # File .o in build/obj
MOC_DIR = $$PWD/build/moc          # File moc in build/moc
RCC_DIR = $$PWD/build/rcc          # File resource compilati in build/rcc
UI_DIR = $$PWD/build/ui            # File UI compilati in build/ui

# Header files
HEADERS += \
    src/gui/AdminDetailPage.h \
    src/gui/AdminPage.h \
    src/gui/BaseDetailPage.h \
    src/gui/BaseEditWidget.h \
    src/gui/BasePage.h \
    src/gui/CdEditWidget.h \
    src/gui/GalleryWidget.h \
    src/gui/LibroEditWidget.h \
    src/gui/LoginPage.h \
    src/gui/MainWindow.h \
    src/gui/MediaBox.h \
    src/gui/MediaCategorySection.h \
    src/gui/MediaEditManager.h \
    src/gui/MediaVideoEditWidget.h \
    src/gui/PeriodicoEditWidget.h \
    src/gui/SearchWidget.h \
    src/gui/UserDetailPage.h \
    src/gui/UserPage.h \
    src/model/media/audiolibro.h \
    src/model/media/biblioteca.h \
    src/model/media/cd.h \
    src/model/media/fumetto.h \
    src/model/media/libro.h \
    src/model/media/media_audio.h \
    src/model/media/media_cartaceo.h \
    src/model/media/media_video.h \
    src/model/media/multimedia.h \
    src/model/media/periodico.h \
    src/model/observers/JsonObserver.h \
    src/model/persistence/JsonManager.h \
    src/model/visitors/Visitor.h \
    src/model/visitors/VisitorWidget.h

# Source files
SOURCES += \
    src/gui/CdEditWidget.cpp \
    src/gui/MediaCategorySection.cpp \
    src/main.cpp \
    src/gui/AdminDetailPage.cpp \
    src/gui/AdminPage.cpp \
    src/gui/BaseDetailPage.cpp \
    src/gui/BaseEditWidget.cpp \
    src/gui/BasePage.cpp \
    src/gui/GalleryWidget.cpp \
    src/gui/LibroEditWidget.cpp \
    src/gui/LoginPage.cpp \
    src/gui/MainWindow.cpp \
    src/gui/MediaBox.cpp \
    src/gui/MediaEditManager.cpp \
    src/gui/MediaVideoEditWidget.cpp \
    src/gui/PeriodicoEditWidget.cpp \
    src/gui/SearchWidget.cpp \
    src/gui/UserDetailPage.cpp \
    src/gui/UserPage.cpp \
    src/model/media/audiolibro.cpp \
    src/model/media/biblioteca.cpp \
    src/model/media/cd.cpp \
    src/model/media/fumetto.cpp \
    src/model/media/libro.cpp \
    src/model/media/media_audio.cpp \
    src/model/media/media_cartaceo.cpp \
    src/model/media/media_video.cpp \
    src/model/media/multimedia.cpp \
    src/model/media/periodico.cpp \
    src/model/persistence/JsonManager.cpp \
    src/model/visitors/VisitorWidget.cpp

