/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkMedianImageFunction.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkMedianImageFunction_h
#define _itkMedianImageFunction_h

#include "itkImageFunction.h"
#include "itkNumericTraits.h"

namespace itk
{

/**
 * \class MedianImageFunction
 * \brief Calculate the median value in the neighborhood of a pixel
 *
 * Calculate the median pixel value over the standard 8, 26, etc. connected
 * neighborhood.  This calculation uses a ZeroFluxNeumannBoundaryCondition.
 *
 * If called with a ContinuousIndex or Point, the calculation is performed
 * at the nearest neighbor.
 *
 * This class is templated over the input image type.
 *
 * \ingroup ImageFunctions
 */
template <class TInputImage >
class ITK_EXPORT MedianImageFunction :
  public ImageFunction< TInputImage, ITK_TYPENAME TInputImage::PixelType >
{
public:
  /** Standard class typedefs. */
  typedef MedianImageFunction Self;
  typedef ImageFunction<TInputImage, NumericTraits<TInputImage::PixelType>::RealType > Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(MedianImageFunction, ImageFunction);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** InputImageType typedef support. */
  typedef TInputImage InputImageType;

  /** OutputType typdef support. */
  typedef typename Superclass::OutputType OutputType;

  /** Index typedef support. */
  typedef typename Superclass::IndexType IndexType;
  
  /** ContinuousIndex typedef support. */
  typedef typename Superclass::ContinuousIndexType ContinuousIndexType;

  /** Point typedef support. */
  typedef typename Superclass::PointType PointType;

  /** Dimension of the underlying image. */
  enum { ImageDimension = InputImageType::ImageDimension };

  /** Datatype used for the mean */
  typedef typename InputImageType::PixelType OutputType;

  /** Evalulate the function at specified index */
  virtual OutputType EvaluateAtIndex( const IndexType& index ) const;
  
  /** Evaluate the function at non-integer positions */
  virtual OutputType Evaluate( const PointType& point ) const
    { 
      IndexType index;
      this->ConvertPointToNearestIndex( point, index );
      return this->EvaluateAtIndex( index ); 
    }
  virtual OutputType EvaluateAtContinuousIndex( 
    const ContinuousIndexType& cindex ) const
    { 
      IndexType index;
      this->ConvertContinuousIndexToNearestIndex( cindex, index );
      return this->EvaluateAtIndex( index ) ; 
    }
  
protected:
  MedianImageFunction();
  ~MedianImageFunction(){};
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  MedianImageFunction( const Self& ); //purposely not implemented
  void operator=( const Self& ); //purposely not implemented

};

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMedianImageFunction.txx"
#endif

#endif

