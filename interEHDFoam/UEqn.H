    MRF.correctBoundaryVelocity(U);

    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U) + fvm::div(rhoPhi, U)
      + MRF.DDt(rho, U)
      + turbulence->divDevRhoReff(rho, U)
     ==
        fvOptions(rho, U)
//       - scalar(0.5)*magSqr(Ef)*fvc::grad(eps)
//       + Ec*Ef
      
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);
    
    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
         ==
            fvc::reconstruct
            (
                (
                    mixture.surfaceTensionForce()
                  - ghf*fvc::snGrad(rho)
                  - fvc::snGrad(p_rgh)
                  - scalar(0.5)*fvc::interpolate(magSqr(Ef))*fvc::snGrad(eps) // Efp
                  - fvc::interpolate(Ec)*fvc::snGrad(Ep) // Efc
                ) * mesh.magSf()
            )
        );

        fvOptions.correct(U);
    }
