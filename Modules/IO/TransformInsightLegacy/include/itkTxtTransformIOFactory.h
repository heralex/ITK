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
#ifndef itkTxtTransformIOFactory_h
#define itkTxtTransformIOFactory_h
#include "ITKIOTransformInsightLegacyExport.h"

#include "itkObjectFactoryBase.h"
#include "itkTransformIOBase.h"

namespace itk
{
/** \class TxtTransformIOFactory
 * \brief Create instances of TxtTransformIO objects using an object factory.
 * \ingroup ITKIOTransformInsightLegacy
 */
class ITKIOTransformInsightLegacy_EXPORT TxtTransformIOFactory : public ObjectFactoryBase
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(TxtTransformIOFactory);

  /** Standard class type aliases. */
  using Self = TxtTransformIOFactory;
  using Superclass = ObjectFactoryBase;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Class methods used to interface with the registered factories. */
  const char *
  GetITKSourceVersion() const override;

  const char *
  GetDescription() const override;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(TxtTransformIOFactory);

  /** Register one factory of this type  */
  static void
  RegisterOneFactory()
  {
    auto metaFactory = TxtTransformIOFactory::New();

    ObjectFactoryBase::RegisterFactoryInternal(metaFactory);
  }

protected:
  TxtTransformIOFactory();
  ~TxtTransformIOFactory() override;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;
};
} // end namespace itk

#endif
