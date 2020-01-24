#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera.h"
#include "scene.h"
#include "geometry.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

QString dir_name;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);

    connect(ui->actionSelect_Path, SIGNAL(triggered(bool)), this, SLOT(on_dirSelected_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dirSelected_clicked()
{
    dir_name = QFileDialog::getExistingDirectory(this, QString("Select Dir"));

    ui->label_Path->setText(dir_name);
}

// Render Button
void MainWindow::on_pushButton_clicked()
{
    if(dir_name.isEmpty())
    {
        QMessageBox::information(this, "NOTE", "Please select a direction path first.");
    }
    else
    {
        // Init scene:
        QImage image(400, 400, QImage::Format_RGB32);
        Camera mainCamera = Camera(400, 400, Point3f(0, 0, 10), Point3f(0, 0, 0), Vector3f(0, 1, 0));
        Scene scene;
        scene.mCamera = mainCamera;

        // Create sphere1 primitive:
        uPtr<Primitive> primSphere1 = mkU<Primitive>(Primitive());
        Transform sphereTransform1 = Transform(Vector3f(0, 0, 1), Vector3f(0, 0, 45), Vector3f(2, 1, 1));
        primSphere1->mName = QString("sphere");
        primSphere1->mUPtrShape = mkU<Sphere>(Sphere());
        primSphere1->mUPtrShape->mTransform = sphereTransform1;
        scene.mPrimitiveList.push_back(std::move(primSphere1));

        // Create sphere2 primitive:
        uPtr<Primitive> primSphere2 = mkU<Primitive>(Primitive());
        Transform sphereTransform2 = Transform(Vector3f(0.25, 0, 0), Vector3f(0, 0, 0), Vector3f(0.5, 0.5, 5));
        primSphere2->mName = QString("sphere");
        primSphere2->mUPtrShape = mkU<Sphere>(Sphere());
        primSphere2->mUPtrShape->mTransform = sphereTransform2;
        scene.mPrimitiveList.push_back(std::move(primSphere2));

        // Create square plane primitive:
        uPtr<Primitive> primSquarePlane = mkU<Primitive>(Primitive());
        Transform squarePlaneTransform = Transform(Vector3f(0, -0.5, 0), Vector3f(90, 0, 0), Vector3f(5, 5, 1));
        primSquarePlane->mName = QString("square");
        primSquarePlane->mUPtrShape = mkU<SquarePlane>(SquarePlane());
        primSquarePlane->mUPtrShape->mTransform = squarePlaneTransform;
        scene.mPrimitiveList.push_back(std::move(primSquarePlane));

        // Rendering:
        for(int rowIdx = 0; rowIdx < 400; rowIdx++)
        {
            for(int colIdx = 0; colIdx < 400; colIdx++)
            {
                // Get a Ray.
                Ray pixel_ray = mainCamera.rayCast(rowIdx, colIdx);
                // Set Color.
                Intersection tempIntersection;
                QRgb value = qRgb(0, 0, 0);

                if(scene.getIntersection(pixel_ray, &tempIntersection))
                {
                    // Hit an obj.
                    glm::vec3 f_color = (tempIntersection.mNormal + glm::vec3(1, 1, 1)) * 0.5f * 255.f;
                    glm::ivec3 i_color = glm::ivec3(f_color);
                    value = qRgb(i_color.x, i_color.y, i_color.z);
                }

                ui->progressBar->setValue(rowIdx * 400 + colIdx);

                image.setPixel(colIdx, rowIdx, value);
            }
        }

        QString file_name = dir_name + "/RenderedResult" + QString(".png");

        image.save(file_name, "PNG");
    }
}
