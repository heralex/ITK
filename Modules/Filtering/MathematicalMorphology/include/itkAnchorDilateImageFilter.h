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
#ifndef itkAnchorDilateImageFilter_h
#define itkAnchorDilateImageFilter_h

#include "itkAnchorErodeDilateImageFilter.h"
#include <functional>

namespace itk
{
template <typename TImage, typename TKernel>
class AnchorDilateImageFilter
  : public AnchorErodeDilateImageFilter<TImage, TKernel, std::greater<typename TImage::PixelType>>

{
public:
  ITK_DISALLOW_COPY_AND_MOVE(AnchorDilateImageFilter);

  using Self = AnchorDilateImageFilter;
  using Superclass = AnchorErodeDilateImageFilter<TImage, TKernel, std::less<typename TImage::PixelType>>;

  /** Runtime information support. */
  itkOverrideGetNameOfClassMacro(AnchorDilateImageFilter);

  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  using PixelType = typename TImage::PixelType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

protected:
  AnchorDilateImageFilter() { this->m_Boundary = NumericTraits<PixelType>::NonpositiveMin(); }
  ~AnchorDilateImageFilter() override = default;

private:
};
} // namespace itk

#endif
