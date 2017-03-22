        eps == alpha1*eps1 + alpha2*eps2;
        sig == alpha1*sig1 + alpha2*sig2;
        
//         solve
//         (
//             fvm::laplacian(sig,Ep)
//         );
// //         solve
// //         (
// //             fvm::laplacian(eps,Ep) + Ec
// //         );
// //         solve
// //         (
// //             fvm::ddt(Ec) 
// //           + fvm::div(phi, Ec)
// //          == fvm::Sp(sig/eps,Ec)
// //         );
// 
//         Ec = -fvc::laplacian(eps,Ep); // electric charge
//         Ef = -fvc::grad(Ep); // electric field intensity
// //         Efp = -scalar(0.5)*magSqr(Ef)*fvc::grad(eps); // polarization term of the electric force
// //         Efc = Ec*Ef; // Coulomb term of the electric force
// //         Eft = Efp + Efc; // total electric force

        
        
        
        
        
        solve
        (
            fvm::laplacian(eps,Ep) + Ec
        );
        solve
        (
            fvm::ddt(Ec)
          + fvm::div(phi,Ec)
         == fvc::laplacian(sig,Ep)
        );
        Ef = -fvc::grad(Ep); // electric field intensity