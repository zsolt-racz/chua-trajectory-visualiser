
#include "crosssectionmap.h"

CrossSectionMap::CrossSectionMap(QCPAxis *keyAxis, QCPAxis *valueAxis):
QCPColorMap(keyAxis, valueAxis){

}

void CrossSectionMap::colorize(const double *data, const QCPRange &range, QRgb *scanLine, int n, int dataIndexFactor, bool logarithmic){
    // If you change something here, make sure to also adapt ::color()
    if (!data)
    {
      qDebug() << Q_FUNC_INFO << "null pointer given as data";
      return;
    }
    if (!scanLine)
    {
      qDebug() << Q_FUNC_INFO << "null pointer given as scanLine";
      return;
    }

    for (int i=0; i<n; ++i){
        std::map<int, std::string>::const_iterator color_it = this->colors.find((int)data[i]);
        if(color_it == this->colors.end()){
            scanLine[i] = QColor("black").rgb();
        }else{
            scanLine[i] = QColor(QString::fromStdString(color_it->second)).rgb();
        }
    }

}

void CrossSectionMap::updateMapImage()
{
  QCPAxis *keyAxis = mKeyAxis.data();
  if (!keyAxis) return;
  if (mMapData->isEmpty()) return;

  const int keySize = mMapData->keySize();
  const int valueSize = mMapData->valueSize();
  int keyOversamplingFactor = mInterpolate ? 1 : (int)(1.0+100.0/(double)keySize); // make mMapImage have at least size 100, factor becomes 1 if size > 200 or interpolation is on
  int valueOversamplingFactor = mInterpolate ? 1 : (int)(1.0+100.0/(double)valueSize); // make mMapImage have at least size 100, factor becomes 1 if size > 200 or interpolation is on

  // resize mMapImage to correct dimensions including possible oversampling factors, according to key/value axes orientation:
  if (keyAxis->orientation() == Qt::Horizontal && (mMapImage.width() != keySize*keyOversamplingFactor || mMapImage.height() != valueSize*valueOversamplingFactor))
    mMapImage = QImage(QSize(keySize*keyOversamplingFactor, valueSize*valueOversamplingFactor), QImage::Format_RGB32);
  else if (keyAxis->orientation() == Qt::Vertical && (mMapImage.width() != valueSize*valueOversamplingFactor || mMapImage.height() != keySize*keyOversamplingFactor))
    mMapImage = QImage(QSize(valueSize*valueOversamplingFactor, keySize*keyOversamplingFactor), QImage::Format_RGB32);

  QImage *localMapImage = &mMapImage; // this is the image on which the colorization operates. Either the final mMapImage, or if we need oversampling, mUndersampledMapImage
  if (keyOversamplingFactor > 1 || valueOversamplingFactor > 1)
  {
    // resize undersampled map image to actual key/value cell sizes:
    if (keyAxis->orientation() == Qt::Horizontal && (mUndersampledMapImage.width() != keySize || mUndersampledMapImage.height() != valueSize))
      mUndersampledMapImage = QImage(QSize(keySize, valueSize), QImage::Format_RGB32);
    else if (keyAxis->orientation() == Qt::Vertical && (mUndersampledMapImage.width() != valueSize || mUndersampledMapImage.height() != keySize))
      mUndersampledMapImage = QImage(QSize(valueSize, keySize), QImage::Format_RGB32);
    localMapImage = &mUndersampledMapImage; // make the colorization run on the undersampled image
  } else if (!mUndersampledMapImage.isNull())
    mUndersampledMapImage = QImage(); // don't need oversampling mechanism anymore (map size has changed) but mUndersampledMapImage still has nonzero size, free it

  const double *rawData = mMapData->mData;
  if (keyAxis->orientation() == Qt::Horizontal)
  {
    const int lineCount = valueSize;
    const int rowCount = keySize;
    for (int line=0; line<lineCount; ++line)
    {
      QRgb* pixels = reinterpret_cast<QRgb*>(localMapImage->scanLine(lineCount-1-line)); // invert scanline index because QImage counts scanlines from top, but our vertical index counts from bottom (mathematical coordinate system)
      this->colorize(rawData+line*rowCount, mDataRange, pixels, rowCount, 1, mDataScaleType==QCPAxis::stLogarithmic);
    }
  } else // keyAxis->orientation() == Qt::Vertical
  {
    const int lineCount = keySize;
    const int rowCount = valueSize;
    for (int line=0; line<lineCount; ++line)
    {
      QRgb* pixels = reinterpret_cast<QRgb*>(localMapImage->scanLine(lineCount-1-line)); // invert scanline index because QImage counts scanlines from top, but our vertical index counts from bottom (mathematical coordinate system)
      this->colorize(rawData+line, mDataRange, pixels, rowCount, lineCount, mDataScaleType==QCPAxis::stLogarithmic);
    }
  }

  if (keyOversamplingFactor > 1 || valueOversamplingFactor > 1)
  {
    if (keyAxis->orientation() == Qt::Horizontal)
      mMapImage = mUndersampledMapImage.scaled(keySize*keyOversamplingFactor, valueSize*valueOversamplingFactor, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    else
      mMapImage = mUndersampledMapImage.scaled(valueSize*valueOversamplingFactor, keySize*keyOversamplingFactor, Qt::IgnoreAspectRatio, Qt::FastTransformation);
  }
  mMapData->mDataModified = false;
  mMapImageInvalidated = false;
}


void CrossSectionMap::updateColors(std::vector<TrajectoryTest>* tests){
    this->colors.clear();


    /** index starts at 1 **/
    for(int i = 0; i < tests->size(); i++){
        this->colors[i+1] = tests->at(i).color;
    }
}
