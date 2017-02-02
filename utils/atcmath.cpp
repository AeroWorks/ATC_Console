
#include "atcmath.h"

double ATCMath::rad2deg(double varRAD)
{
    return varRAD * 180 / ATCConst::PI;
}

double ATCMath::deg2rad(double varDEG)
{
    return varDEG * ATCConst::PI / 180;
}

double ATCMath::m2nm(double varM)
{
    return varM / 1852;
}

double ATCMath::nm2m(double varNM)
{
    return varNM * 1852;
}

double ATCMath::m2ft(double varM)
{
    return varM / 0.3048;
}

double ATCMath::ft2m(double varFT)
{
    return varFT * 0.3048;
}

double ATCMath::mps2kt(double varMPS)
{
    return varMPS * 1.94384449;
}

double ATCMath::kt2mps(double varKT)
{
    return varKT * 0.51444444;
}

double ATCMath::cas2tas(double casMPS, double p, double rho)
{
    double p0 = 101325;
    double rho0 = 1.225;
    double kappa = 1.4;
    double mi = (kappa - 1) / kappa;

    double tasMPS = qPow(2/mi * p/rho * (qPow(1 + p0/p * (qPow(1 + mi/2 * rho0/p0 * qPow(casMPS, 2), 1/mi) - 1), mi) -1), 0.5);

    return tasMPS;
}

double ATCMath::cas2mach(double casMPS, double p, double rho, double a)
{
    return ATCMath::cas2tas(casMPS, p, rho) / a;
}

double ATCMath::tas2cas(double tasMPS, double p, double rho)
{
    double p0 = 101325;
    double rho0 = 1.225;
    double kappa = 1.4;
    double mi = (kappa - 1) / kappa;

    double casMPS = qPow(2/mi * p0/rho0 * (qPow(1 + p/p0 * (qPow(1 + mi/2 * rho/p * qPow(tasMPS, 2), 1/mi) - 1), mi) -1), 0.5);

    return casMPS;
}

double ATCMath::tas2mach(double tasMPS, double a)
{
    return tasMPS / a;
}

double ATCMath::mach2tas(double mach, double a)
{
    return mach * a;
}

double ATCMath::mach2cas(double mach, double p, double rho, double a)
{
    return ATCMath::tas2cas(mach * a, p, rho);
}

bool ATCMath::compareDouble(double numActual, double numModel, double allowedError)
{
    if(numModel != 0)
        if((numActual >= numModel - qFabs(numModel) * allowedError) && (numActual <= numModel + qFabs(numModel) * allowedError))
        {
            return true;
        }
        else
        {
            return false;
        }
    else
    {
        if((numActual >= numModel - allowedError) && (numActual <= numModel + allowedError))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

double ATCMath::min(double a, double b)
{
    return (a < b) ? a : b;
}

double ATCMath::max(double a, double b)
{
    return (a > b) ? a : b;
}

ISA ATCMath::atmosISA(double h)
{
    ISA isa;

    double betaTrop = ATCConst::betaTrop;
    double betaStrat1 = ATCConst::betaStrat1;
    double betaStrat2 = ATCConst::betaStrat2;
    double betaMeso1 = ATCConst::betaMeso1;
    double betaMeso2 = ATCConst::betaMeso2;

    double kappa = ATCConst::kappa;
    double R = ATCConst::R;

    double gN = ATCConst::g0;

    //Calculate temperature
    if((h >= -2000) && (h < 11000))
    {
        isa.T = 288.15 + betaTrop * (h - 0);
    }
    else if((h >= 11000) && (h < 20000))
    {
        isa.T = 216.65;
    }
    else if((h >= 20000) && (h < 32000))
    {
        isa.T = 216.65 + betaStrat1 * (h - 20000);
    }
    else if((h >= 32000) && (h < 47000))
    {
        isa.T = 228.65 + betaStrat2 * (h - 32000);
    }
    else if((h >= 47000) && (h < 51000))
    {
        isa.T = 270.65;
    }
    else if((h >= 51000) && (h < 71000))
    {
        isa.T = 270.65 + betaMeso1 * (h - 51000);
    }
    else if((h >= 71000) && (h <= 80000))
    {
        isa.T = 214.65 + betaMeso2 * (h - 71000);
    }
    else
    {
        isa.T = -1;
    }

    //Calculate pressure
    if((h >= -2000) && (h < 11000))
    {
        isa.p = 101325 * qPow((1 + betaTrop/288.15 * (h - 0)), -gN/(betaTrop * R));
    }
    else if((h >= 11000) && (h < 20000))
    {
        isa.p = 22632.1 * qExp(-gN/(R * isa.T) * (h - 11000));
    }
    else if((h >= 20000) && (h < 32000))
    {
        isa.p = 5474.89 * qPow((1 + betaStrat1/216.65 * (h - 20000)), -gN/(betaStrat1 * R));
    }
    else if((h >= 32000) && (h < 47000))
    {
        isa.p = 868.019 * qPow((1 + betaStrat2/228.65 * (h - 32000)), -gN/(betaStrat2 * R));
    }
    else if((h >= 47000) && (h < 51000))
    {
        isa.p = 110.906 * qExp(-gN/(R * isa.T) * (h - 47000));
    }
    else if((h >= 51000) && (h < 71000))
    {
        isa.p = 66.9389 * qPow((1 + betaMeso1/270.65 * (h - 51000)), -gN/(betaMeso1 * R));
    }
    else if((h >= 71000) && (h <= 80000))
    {
        isa.p = 3.95642 * qPow((1 + betaMeso2/214.65 * (h - 71000)), -gN/(betaMeso2 * R));
    }
    else
    {
        isa.p = -1;
    }

    //Calculate air density
    if((h >= -2000) && (h <= 80000))
    {
        isa.rho = isa.p / (R * isa.T);
    }
    else
    {
        isa.rho = -1;
    }

    //Calculate sound velocity
    if((h >= -2000) && (h <= 80000))
    {
        isa.a = qSqrt(kappa * R * isa.T);
    }
    else
    {
        isa.a = -1;
    }

    return isa;
}

double ATCMath::crossoverAltitude(double casMPS, double M)
{
    ISA isa = atmosISA(0);

    double kappa = 1.4;
    double a0 = isa.a;
    double t0 = isa.T;
    double R = 287.05287;
    double betaTrop = -0.0065;
    double g0 = 9.80665;

    double deltaTrans = (qPow((1 + (kappa-1)/2 * qPow(casMPS/a0, 2)), kappa/(kappa - 1)) - 1) / (qPow((1 + (kappa-1)/2 * qPow(M, 2)), kappa/(kappa-1)) - 1);
    double thetaTrans = qPow(deltaTrans, -1 * betaTrop * R / g0);
    double HpTrans = 1000 / 6.5 * t0 * (1 - thetaTrans);

    return HpTrans;
}

double ATCMath::normalizeAngle(double angle, ATC::AngularUnits unitType)
{
    double normAngle;

    if(unitType == ATC::Rad)
    {
        int k = qFloor(qFabs(angle) / (2 * ATCConst::PI));

        if(angle > 0)
        {
            normAngle = angle - k * 2 * ATCConst::PI;
        }
        else
        {
            normAngle = angle + (k + 1) * 2 * ATCConst::PI;
        }
    }
    else
    {
        int k = qFloor(qFabs(angle) / 360);

        if(angle > 0)
        {
            normAngle = angle - k * 360;
        }
        else
        {
            normAngle = angle + (k + 1) * 360;
        }
    }

    return normAngle;
}

double ATCMath::ESF(BADA::ClimbMode cm, BADA::AccelerationMode am, BADA::SpeedHoldMode shm, BADA::TroposphereMode trm, double mach, double temp, double dTemp)
{
    double betaTrop = ATCConst::betaTrop;
    double kappa = ATCConst::kappa;
    double R = ATCConst::R;
    double g0 = ATCConst::g0;

    double ESF;

    if(cm == BADA::Level)
    {
        ESF = 0;
    }
    else if(cm == BADA::Descend)
    {
        if(am == BADA::Constant)
        {
            if(shm == BADA::CAS)
            {
                if(trm == BADA::Low)
                {
                    ESF = qPow(1 + (kappa*R*betaTrop)/(2*g0) * qPow(mach, 2) * (temp - dTemp)/temp + qPow(1 + (kappa-1)/2 * qPow(mach, 2), -1/(kappa-1)) * (qPow(1 + (kappa-1)/2 * qPow(mach, 2), kappa/(kappa-1)) -1), -1);
                }
                else //High
                {
                    ESF = qPow(1 + qPow(1 + (kappa-1)/2 * qPow(mach, 2), -1/(kappa-1)) * (qPow(1 + (kappa-1)/2 * qPow(mach, 2), kappa/(kappa-1)) - 1), -1);
                }
            }
            else
            {
                if(trm == BADA::Low)
                {
                    ESF = qPow(1 + (kappa*R*betaTrop)/(2*g0) * qPow(mach, 2) * (temp - dTemp)/temp, -1);
                }
                else //High
                {
                    ESF = 1;
                }
            }
        }
        else if(am == BADA::Decelerate)
        {
            ESF = 0.3;
        }
        else //Accelerate
        {
            ESF = 1.7;
        }
    }
    else //Climb
    {
        if(am == BADA::Constant)
        {
            if(shm == BADA::CAS)
            {
                if(trm == BADA::Low)
                {
                    ESF = qPow(1 + (kappa*R*betaTrop)/(2*g0) * qPow(mach, 2) * (temp - dTemp)/temp + qPow(1 + (kappa-1)/2 * qPow(mach, 2), -1/(kappa-1)) * (qPow(1 + (kappa-1)/2 * qPow(mach, 2), kappa/(kappa-1)) -1), -1);
                }
                else //High
                {
                    ESF = qPow(1 + qPow(1 + (kappa-1)/2 * qPow(mach, 2), -1/(kappa-1)) * (qPow(1 + (kappa-1)/2 * qPow(mach, 2), kappa/(kappa-1)) - 1), -1);
                }
            }
            else
            {
                if(trm == BADA::Low)
                {
                    ESF = qPow(1 + (kappa*R*betaTrop)/(2*g0) * qPow(mach, 2) * (temp - dTemp)/temp, -1);
                }
                else //High
                {
                    ESF = 1;
                }
            }
        }
        else if(am == BADA::Decelerate)
        {
            ESF = 1.7;
        }
        else //Accelerate
        {
            ESF = 0.3;
        }
    }

    return ESF;
}

double ATCMath::randomMass(int mMin, int mMax)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    return mMin + qrand() % (mMax - mMin + 1);
}

double ATCMath::recalculateSpeed(double vRef, double m, double mRef)
{
    return vRef * sqrt(m / mRef);
}

double ATCMath::recalculateReductionFactor(double Cred, double m, double mMin, double mMax)
{
    return 1 - Cred * (mMax - m) / (mMax - mMin);
}

double ATCMath::nominalSpeedCL(double currentAltM, BADA::SpeedHoldMode shm, ATC::EngineType engine, double vStallTO, double vCL1, double vCL2, double machCL, double a, double rho, double p)
{
    double Vnom;
    double CVmin = ATCConst::C_V_MIN;

    if(engine == ATC::Jet)
    {
        if(shm == BADA::Mach)
        {
            Vnom = machCL;
        }
        else if((currentAltM >= 3048) && (shm == BADA::CAS)) //Above 10000ft
        {
            Vnom = vCL2;
        }
        else if((currentAltM >= 1828.8) && (currentAltM < 3048)) //6000ft - 10000ft
        {
            Vnom = ATCMath::min(vCL1, 250);
        }
        else if((currentAltM >= 1524) && (currentAltM < 1828.8)) //5000ft - 6000ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL5;
        }
        else if((currentAltM >= 1219.2) && (currentAltM < 1524)) //4000ft - 5000ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL4;
        }
        else if((currentAltM >= 914.4) && (currentAltM < 1219.2)) //3000ft - 4000ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL3;
        }
        else if((currentAltM >= 457.2) && (currentAltM < 914.4)) //1500ft - 3000ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL2;
        }
        else if(currentAltM < 457.2) //Below 1500ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL1;
        }
    }
    else
    {
        if(shm == BADA::Mach)
        {
            Vnom = machCL;
        }
        else if((currentAltM >= 3048) && (shm == BADA::CAS)) //Above 10000ft
        {
            Vnom = vCL2;
        }
        else if((currentAltM >= 457.2) && (currentAltM < 3048)) //1500ft - 10000ft
        {
            Vnom = ATCMath::min(vCL1, 250);
        }
        else if((currentAltM >= 304.8) && (currentAltM < 457.2)) //1000ft - 1500ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL8;
        }
        else if((currentAltM >= 152.4) && (currentAltM < 304.8)) //500ft - 1000ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL7;
        }
        else if(currentAltM < 152.4) //Below 500ft
        {
            Vnom = CVmin * vStallTO + ATCConst::V_CL6;
        }
    }

    return ATCMath::nominalSpeed2tas(Vnom, shm, a, rho, p);
}

double ATCMath::nominalSpeedCR(double currentAltM, BADA::SpeedHoldMode shm, ATC::EngineType engine, double vCR1, double vCR2, double machCR, double a, double rho, double p)
{
    double Vnom;

    if(engine == ATC::Jet)
    {
        if(shm == BADA::Mach)
        {
            Vnom = machCR;
        }
        else if((currentAltM >= 4267.2) && (shm == BADA::CAS)) //Above 14000ft
        {
            Vnom = vCR2;
        }
        else if((currentAltM >= 1828.8) && (currentAltM < 4267.2)) //6000ft - 14000ft
        {
            Vnom = ATCMath::min(vCR1, 250);
        }
        else if((currentAltM >= 914.4) && (currentAltM < 1828.8)) //3000ft - 6000ft
        {
            Vnom = ATCMath::min(vCR1, 220);
        }
        else if(currentAltM < 914.4) //Below 3000ft
        {
            Vnom = ATCMath::min(vCR1, 170);
        }
    }
    else
    {
        if(shm == BADA::Mach)
        {
            Vnom = machCR;
        }
        else if((currentAltM >= 3048) && (shm == BADA::CAS)) //Above 10000ft
        {
            Vnom = vCR2;
        }
        else if((currentAltM >= 1828.8) && (currentAltM < 3048)) //6000ft - 10000ft
        {
            Vnom = ATCMath::min(vCR1, 250);
        }
        else if((currentAltM >= 914.4) && (currentAltM < 1828.8)) //3000ft - 6000ft
        {
            Vnom = ATCMath::min(vCR1, 180);
        }
        else if(currentAltM < 914.4) //Below 3000ft
        {
            Vnom = ATCMath::min(vCR1, 150);
        }
    }

    return ATCMath::nominalSpeed2tas(Vnom, shm, a, rho, p);
}

double ATCMath::nominalSpeedDS(double currentAltM, BADA::SpeedHoldMode shm, ATC::EngineType engine, double vStallLD, double vDS1, double vDS2, double machDS, double a, double rho, double p)
{
    double Vnom;
    double CVmin = ATCConst::C_V_MIN;

    if((engine == ATC::Jet) || (engine == ATC::Turboprop))
    {
        if(shm == BADA::Mach)
        {
            Vnom = machDS;
        }
        else if((currentAltM >= 3048) && (shm == BADA::CAS)) //Above 10000ft
        {
            Vnom = vDS2;
        }
        else if((currentAltM >= 1828.8) && (currentAltM < 3048)) //6000ft - 10000ft
        {
            Vnom = ATCMath::min(vDS1, 250);
        }
        else if((currentAltM >= 914.4) && (currentAltM < 1828.8)) //3000ft - 6000ft
        {
            Vnom = ATCMath::min(vDS1, 220);
        }
        else if((currentAltM >= 609.6) && (currentAltM < 914.4)) //2000ft - 3000ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES4;
        }
        else if((currentAltM >= 457.2) && (currentAltM < 609.6)) //1500ft - 2000ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES3;
        }
        else if((currentAltM >= 304.8) && (currentAltM < 457.2)) //1000ft - 1500ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES2;
        }
        else if(currentAltM < 304.8) //Below 1000ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES1;
        }
    }
    else
    {
        if(shm == BADA::Mach)
        {
            Vnom = machDS;
        }
        else if((currentAltM >= 3048) && (shm == BADA::CAS)) //Above 10000ft
        {
            Vnom = vDS2;
        }
        else if((currentAltM >= 457.2) && (currentAltM < 3048)) //1500ft - 10000ft
        {
            Vnom = vDS1;
        }
        else if((currentAltM >= 304.8) && (currentAltM < 457.2)) //1000ft - 1500ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES7;
        }
        else if((currentAltM >= 152.4) && (currentAltM < 304.8)) //500ft - 1000ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES6;
        }
        else if(currentAltM < 152.4) //Below 500ft
        {
            Vnom = CVmin * vStallLD + ATCConst::V_DES5;
        }
    }

    return ATCMath::nominalSpeed2tas(Vnom, shm, a, rho, p);
}

double ATCMath::nominalSpeed2tas(double vNom, BADA::SpeedHoldMode shm, double a, double rho, double p)
{
    double tasNomMPS;

    if(shm == BADA::CAS)
    {
        tasNomMPS = ATCMath::cas2tas(ATCMath::kt2mps(vNom), p, rho);
    }
    else
    {
        tasNomMPS = a * vNom;
    }

    return tasNomMPS;
}

BADA::ClimbMode ATCMath::assignCM(double currentAltM, double targetAltM)
{
    double diff = currentAltM - targetAltM;

    if(qFabs(diff) <= 1)
    {
        return BADA::Level;
    }
    else if(diff > 0)
    {
        return BADA::Descend;
    }
    else if(diff < 0)
    {
        return BADA::Climb;
    }

    return BADA::ErrorCM;
}

BADA::FlightPhase ATCMath::assignFP(double currentAltM, double altDesM, double tasMPS, double Vdes1KT, double p, double rho)
{
    double casKT = ATCMath::mps2kt(ATCMath::tas2cas(tasMPS, p, rho));

    double v1KT;
    double v2KT;

    (Vdes1KT > 220) ? (v1KT = 230) : (v1KT = Vdes1KT + 10);
    (Vdes1KT > 250) ? (v2KT = 260) : (v2KT = Vdes1KT + 10);

    if(currentAltM >= altDesM)
    {
        return BADA::UpperDescent;
    }
    else if((currentAltM < altDesM) && ((casKT >= v2KT) || (currentAltM >= 2438.4))) //8000ft
    {
        return BADA::LowerDescent;
    }
    else if(((casKT < v2KT) && (currentAltM < 2438.4)) && ((casKT >= v1KT) || (currentAltM >= 914.4)))
    {
        return BADA::Approach;
    }
    else if((casKT < v1KT) && (currentAltM < 914.4)) //3000ft
    {
        return BADA::Landing;
    }

    return BADA::ErrorFP;
}

BADA::ReducedPowerMode ATCMath::assignRPM(double currentAltM, double altMax)
{
    if(currentAltM >= 0.8 * altMax)
    {
        return BADA::Off;
    }
    else
    {
        return BADA::On;
    }

    return BADA::ErrorRPM;
}

BADA::SpeedHoldMode ATCMath::assignSHM(double currentAltM, BADA::ClimbMode cm, double xoverAltClbM, double xoverAltCrsM, double xoverAltDesM)
{
    if(((cm == BADA::Level) && (currentAltM >= xoverAltCrsM)) ||
       ((cm == BADA::Descend) && (currentAltM >= xoverAltDesM)) ||
       ((cm == BADA::Climb) && (currentAltM >= xoverAltClbM)))
    {
        return BADA::Mach;
    }
    else
    {
        return BADA::CAS;
    }

    return BADA::ErrorSHM;
}

BADA::TroposphereMode ATCMath::assignTRM(double currentAltM)
{
    if(currentAltM <= 11000)
    {
        return BADA::Low;
    }
    else
    {
        return BADA::High;
    }

    return BADA::ErrorTRM;
}

BADA::AccelerationMode ATCMath::assignAM(double tasMPS, double tasNomMPS)
{
    if(qFabs(tasMPS - tasNomMPS) <= 1)
    {
        return BADA::Constant;
    }
    else if(tasMPS - tasNomMPS > 1)
    {
        return BADA::Decelerate;
    }
    else if(tasMPS - tasNomMPS < -1)
    {
        return BADA::Accelerate;
    }

    return BADA::ErrorAM;
}

