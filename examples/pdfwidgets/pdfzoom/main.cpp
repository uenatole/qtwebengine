#include <QApplication>
#include <QPdfDocument>
#include <QPdfView>
#include <qevent.h>
#include <qprocess.h>
#include <qtimer.h>

class CustomPdfView : public QPdfView
{
public:
    using QPdfView::QPdfView;

protected:
    void wheelEvent(QWheelEvent* event) override
    {
        if (event->modifiers() & Qt::ControlModifier) {
            int delta = event->angleDelta().y();

            if (delta == 0) {
                event->ignore();
                return;
            }

            qreal currentZoom = zoomFactor();
            qreal stepSize = calculateZoomStep(currentZoom, (delta > 0) ? +1 : -1);

            qreal zoomChange = (delta > 0) ? stepSize : -stepSize;
            qreal newZoomFactor = qBound(0.1, currentZoom + zoomChange, 10.0);

            setZoomFactor(newZoomFactor);
            event->accept();
        } else {
            QPdfView::wheelEvent(event);
        }
    }

private:
    static qreal calculateZoomStep(qreal currentZoomFactor, int sign)
    {
        constexpr qreal baseStep = 0.1;
        constexpr qreal ceilStep = 0.9;

        const auto factor = std::ceil(currentZoomFactor + sign * baseStep);
        return qMin(baseStep * factor, ceilStep);
    }
};

int main(int argc, char** argv)
{
    QPdfDocument document;
    document.load(qgetenv("PDFZOOM_DOCUMENT_PATH"));

    QApplication app(argc, argv);

    CustomPdfView view;
    view.setGeometry(QRect(0, 0, 640, 480));
    view.setDocument(&document);
    view.show();

    return QApplication::exec();
}