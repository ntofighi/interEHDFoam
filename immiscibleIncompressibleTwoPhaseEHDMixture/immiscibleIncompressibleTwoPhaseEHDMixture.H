/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2014-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::immiscibleIncompressibleTwoPhaseEHDMixture

Description
    An immiscible incompressible two-phase EHD mixture transport model

SourceFiles
    immiscibleIncompressibleTwoPhaseEHDMixture.C

\*---------------------------------------------------------------------------*/
/* Electrohydrodynamics additions by Nima Tofighi (C) 2017
   ntofighi@uvic.ca
\*---------------------------------------------------------------------------*/



#ifndef immiscibleIncompressibleTwoPhaseEHDMixture_H
#define immiscibleIncompressibleTwoPhaseEHDMixture_H

#include "incompressibleTwoPhaseMixture.H"
#include "interfaceProperties.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
           Class immiscibleIncompressibleTwoPhaseEHDMixture Declaration
\*---------------------------------------------------------------------------*/

class immiscibleIncompressibleTwoPhaseEHDMixture
:
    public incompressibleTwoPhaseMixture,
    public interfaceProperties
{
protected:
    
    // Protected data
    
        dimensionedScalar eps1_; // ADD
        dimensionedScalar eps2_; // ADD
        
        dimensionedScalar sig1_; // ADD
        dimensionedScalar sig2_; // ADD

        
public:

    // Constructors

        //- Construct from components
        immiscibleIncompressibleTwoPhaseEHDMixture
        (
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~immiscibleIncompressibleTwoPhaseEHDMixture()
    {}


    // Member Functions
    
        //- Return const-access to phase1 absolute electric permittivity // ADD
        const dimensionedScalar& eps1() const
        {
            return eps1_;
        }

        //- Return const-access to phase2 absolute electric permittivity // ADD
        const dimensionedScalar& eps2() const
        {
            return eps2_;
        };
        
        //- Return const-access to phase1 electric conductivity // ADD
        const dimensionedScalar& sig1() const
        {
            return sig1_;
        }

        //- Return const-access to phase2 electric conductivity // ADD
        const dimensionedScalar& sig2() const
        {
            return sig2_;
        };

        //- Correct the transport and interface properties
        virtual void correct()
        {
            incompressibleTwoPhaseMixture::correct();
            interfaceProperties::correct();
        }

        //- Read base transportProperties dictionary
        virtual bool readadd();
        
        virtual bool read()
        {
            return
                immiscibleIncompressibleTwoPhaseEHDMixture::readadd()
             && interfaceProperties::read();
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
