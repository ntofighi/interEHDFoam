/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2014 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/
/* Electrohydrodynamics additions by Nima Tofighi (C) 2017
   ntofighi@uvic.ca
\*---------------------------------------------------------------------------*/

#include "immiscibleIncompressibleTwoPhaseEHDMixture.H"


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::immiscibleIncompressibleTwoPhaseEHDMixture::
immiscibleIncompressibleTwoPhaseEHDMixture
(
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    incompressibleTwoPhaseMixture(U, phi),
    interfaceProperties(alpha1(), U, *this),
    
    eps1_("eps", dimensionSet(-1, -3, 4, 0, 0, 2, 0), nuModel1_->viscosityProperties()), // ADD
    eps2_("eps", dimensionSet(-1, -3, 4, 0, 0, 2, 0), nuModel2_->viscosityProperties()), // ADD
    
    sig1_("sig", dimensionSet(-1, -3, 3, 0, 0, 2, 0), nuModel1_->viscosityProperties()), // ADD
    sig2_("sig", dimensionSet(-1, -3, 3, 0, 0, 2, 0), nuModel2_->viscosityProperties())  // ADD
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::immiscibleIncompressibleTwoPhaseEHDMixture::readadd() // ADD
{
    if (regIOobject::read())
    {
        if
        (
            nuModel1_().read
            (
                subDict(phase1Name_ == "1" ? "phase1": phase1Name_)
            )
         && nuModel2_().read
            (
                subDict(phase2Name_ == "2" ? "phase2": phase2Name_)
            )
        )
        {
            nuModel1_->viscosityProperties().lookup("rho") >> rho1_;
            nuModel2_->viscosityProperties().lookup("rho") >> rho2_;
            
            nuModel1_->viscosityProperties().lookup("eps") >> eps1_;
            nuModel2_->viscosityProperties().lookup("eps") >> eps2_;
            
            nuModel1_->viscosityProperties().lookup("sig") >> sig1_;
            nuModel2_->viscosityProperties().lookup("sig") >> sig2_;

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// ************************************************************************* //
