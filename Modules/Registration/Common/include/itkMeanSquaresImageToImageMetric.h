/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkMeanSquaresImageToImageMetric_h
#define itkMeanSquaresImageToImageMetric_h

#include "itkImageToImageMetric.h"
#include "itkPoint.h"
#include "itkIndex.h"

#include <memory> // For unique_ptr.


namespace itk
{

/**
 * \class MeanSquaresImageToImageMetric
 * \brief TODO
 * \ingroup ITKRegistrationCommon
 *
 * \sphinx
 * \sphinxexample{Registration/Common/ComputeMeanSquareBetweenTwoImages,Compute Mean Squares Metric Between Two Images}
 * \endsphinx
 */
template <typename TFixedImage, typename TMovingImage>
class ITK_TEMPLATE_EXPORT MeanSquaresImageToImageMetric : public ImageToImageMetric<TFixedImage, TMovingImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(MeanSquaresImageToImageMetric);

  /** Standard class type aliases. */
  using Self = MeanSquaresImageToImageMetric;
  using Superclass = ImageToImageMetric<TFixedImage, TMovingImage>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(MeanSquaresImageToImageMetric);

  /** Types inherited from Superclass. */
  using typename Superclass::TransformType;
  using typename Superclass::TransformPointer;
  using typename Superclass::TransformJacobianType;
  using typename Superclass::InterpolatorType;
  using typename Superclass::MeasureType;
  using typename Superclass::DerivativeType;
  using typename Superclass::ParametersType;
  using typename Superclass::FixedImageType;
  using typename Superclass::MovingImageType;
  using typename Superclass::MovingImagePointType;
  using typename Superclass::FixedImageConstPointer;
  using typename Superclass::MovingImageConstPointer;
  using typename Superclass::CoordinateRepresentationType;
  using typename Superclass::FixedImageSampleContainer;
  using typename Superclass::ImageDerivativesType;
  using typename Superclass::WeightsValueType;
  using typename Superclass::IndexValueType;

  // Needed for evaluation of Jacobian.
  using typename Superclass::FixedImagePointType;

  /** The moving image dimension. */
  static constexpr unsigned int MovingImageDimension = MovingImageType::ImageDimension;

  /**
   *  Initialize the Metric by
   *  (1) making sure that all the components are present and plugged
   *      together correctly,
   *  (2) uniformly select NumberOfSpatialSamples within
   *      the FixedImageRegion, and
   *  (3) allocate memory for pdf data structures. */
  void
  Initialize() override;

  /**  Get the value. */
  MeasureType
  GetValue(const ParametersType & parameters) const override;

  /** Get the derivatives of the match measure. */
  void
  GetDerivative(const ParametersType & parameters, DerivativeType & derivative) const override;

  /**  Get the value and derivatives for single valued optimizers. */
  void
  GetValueAndDerivative(const ParametersType & parameters,
                        MeasureType &          value,
                        DerivativeType &       derivative) const override;

protected:
  MeanSquaresImageToImageMetric();
  ~MeanSquaresImageToImageMetric() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  bool
  GetValueThreadProcessSample(ThreadIdType                 threadId,
                              SizeValueType                fixedImageSample,
                              const MovingImagePointType & mappedPoint,
                              double                       movingImageValue) const override;

  bool
  GetValueAndDerivativeThreadProcessSample(ThreadIdType                 threadId,
                                           SizeValueType                fixedImageSample,
                                           const MovingImagePointType & mappedPoint,
                                           double                       movingImageValue,
                                           const ImageDerivativesType & movingImageGradientValue) const override;

  struct PerThreadS
  {
    TransformJacobianType m_Jacobian;
    MeasureType           m_MSE;
    DerivativeType        m_MSEDerivative;
  };

  itkAlignedTypedef(64, PerThreadS, AlignedPerThreadType);
  std::unique_ptr<AlignedPerThreadType[]> m_PerThread;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkMeanSquaresImageToImageMetric.hxx"
#endif

#endif
