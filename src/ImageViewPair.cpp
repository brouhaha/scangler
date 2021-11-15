#include "ImageViewPair.h"

ImageViewPair::ImageViewPair (QImage *i1, QImage *i2, QWidget *parent, Qt::WindowFlags f) : QWidget (parent, f)
{
  image [0] = i1;
  image [1] = i2;
  for (int i = 0; i < 2; i++)
    imageView [i] = new ImageView (image [i], this);

  for (int i = 0; i < 2; i++)
    {
      connect (imageView [i]->horizontalScrollBar (),
	       SIGNAL (valueChanged (int)),
	       imageView [! i]->horizontalScrollBar (),
	       SLOT (setValue (int)));
      connect (imageView [i]->verticalScrollBar (),
	       SIGNAL (valueChanged (int)),
	       imageView [! i]->verticalScrollBar (),
	       SLOT (setValue (int)));
    }

  orientation = Horizontal;

  layout = new QGridLayout (this);
  for (int i = 0; i <= 1; i++)
    {
      layout->addWidget (imageView [i], 0, i);
      printf ("adding %d at row 0 col %d\n", i, i);
    }
  for (int i = 0; i <= 1; i++)
    printf ("image %d at index %d\n", i, layout->indexOf (imageView [i]));
  setLayout (layout);
}

void ImageViewPair::setImage (int n, QImage *i)
{
  imageView [n]->setImage (i);
}

void ImageViewPair::setOrientation (enum Orientation orientation)
{
  if (orientation == this->orientation)
    return;
  switch (this->orientation)
    {
    case Horizontal:
    case Vertical:
      printf ("removing image 0\n");
      layout->removeWidget (imageView [0]);
      printf ("removing image 1\n");
      layout->removeWidget (imageView [1]);
      break;
    case Only0:
      printf ("removing image 0\n");
      layout->removeWidget (imageView [0]);
      break;
    case Only1:
      printf ("removing image 1\n");
      layout->removeWidget (imageView [1]);
      break;
    }

  switch (orientation)
    {
    case Horizontal:
      printf ("adding 0 at row 0 col 0\n");
      layout->addWidget (imageView [0], 0, 0);
      printf ("adding 1 at row 0 col 1\n");
      layout->addWidget (imageView [1], 0, 1);
      break;
    case Vertical:
      printf ("adding 0 at row 0 col 0\n");
      layout->addWidget (imageView [0], 0, 0);
      printf ("adding 1 at row 1 col 0\n");
      layout->addWidget (imageView [1], 1, 0);
      break;
    case Only0:
      printf ("adding 0 at row 0 col 0\n");
      layout->addWidget (imageView [0], 0, 0);
      break;
    case Only1:
      printf ("adding 1 at row 0 col 0\n");
      layout->addWidget (imageView [1], 0, 0);
      break;
    }

  for (int i = 0; i <= 1; i++)
    printf ("image %d at index %d\n", i, layout->indexOf (imageView [i]));

  this->orientation = orientation;
}
