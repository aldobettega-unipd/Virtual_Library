#ifndef MEDIAVIDEOEDITWIDGET_H
#define MEDIAVIDEOEDITWIDGET_H

#include "BaseEditWidget.h"
#include "../model/media/media_video.h"

class MediaVideoEditWidget : public BaseEditWidget
{
    Q_OBJECT
public:
    explicit MediaVideoEditWidget(QWidget* parent = nullptr);

    // implementazione metodi virtuali
    void setMedia(Biblioteca* media) override;
    Biblioteca* createMedia() override;
    void updateMedia() override;
    void clearFields() override;
    bool validateFields() override;

private:
    QLineEdit* registaEdit;

    Media_video* currentMediaVideo;

    void setupUI();

    void populateMediaVideoFields(Media_video* video);
    void clearMediaVideoFields();
    bool validateMediaVideoFields();

};

#endif // MEDIAVIDEOEDITWIDGET_H
