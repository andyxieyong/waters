clear all

histResolution = 100;
xLabelText = "Time (us)";
yLabelText = "Count";
unit = 1000;

graphics_toolkit("gnuplot")


addpath ("../../build/examples/waters")

FF_1 = load("Chain_EffectChain_1_FF.txt") ./ unit;
LL_1 = load("Chain_EffectChain_1_LL.txt") ./ unit;
FF_2 = load("Chain_EffectChain_2_FF.txt") ./ unit;
LL_2 = load("Chain_EffectChain_2_LL.txt") ./ unit;

#FF_3 = load("Chain_EffectChain_3_FF.txt");
#LL_3 = load("Chain_EffectChain_3_LL.txt");

subplot(2,2,1)
hist(FF_1, histResolution);
title("Chain 1: First-to-Fist");
xlabel(xLabelText);
ylabel(yLabelText);

subplot(2,2,2)
hist(FF_2, histResolution);
title("Chain 2: First-to-Fist");
xlabel(xLabelText);
ylabel(yLabelText);

subplot(2,2,3)
hist(LL_1, histResolution);
title("Chain 1: Last-to-Last");
xlabel(xLabelText);
ylabel(yLabelText);

subplot(2,2,4)
hist(LL_2, histResolution);
title("Chain 2: Last-to-Last");
xlabel(xLabelText);
ylabel(yLabelText);