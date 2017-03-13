        eps == alpha1*eps1 + alpha2*eps2;
        sig == alpha1*sig1 + alpha2*sig2;
        
        solve
        (
            fvm::laplacian(sig,Ep)
        );
        
        Ec = fvc::laplacian(eps,Ep); // electric charge
        Ef = -fvc::grad(Ep); // electric field intensity
        Efp = -scalar(0.5)*magSqr(Ef)*fvc::grad(eps); // polarization term of the electric force
        Efc = Ec*Ef; // Coulomb term of the electric force
        Eft = Efp + Efc; // total electric force
