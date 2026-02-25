/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{
    deallocateSignals();
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->midiin_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_07_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_08_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_09_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_10_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_11_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_12_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 1;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    this->poly_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 4; i++) {
        this->poly[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 1:
        {
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    for (Index i = 0; i < 4; i++) {
        this->poly[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);

    this->RNBODefaultSinus = initDataRef(
        this->RNBODefaultSinus,
        this->dataRefStrings->name0,
        true,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->RNBODefaultMtofLookupTable256 = initDataRef(
        this->RNBODefaultMtofLookupTable256,
        this->dataRefStrings->name1,
        true,
        this->dataRefStrings->file1,
        this->dataRefStrings->tag1
    );

    this->assign_defaults();
    this->applyState();
    this->RNBODefaultSinus->setIndex(0);
    this->RNBODefaultMtofLookupTable256->setIndex(1);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        for (Index i = 0; i < 4; i++) {
            this->poly[i]->processTempoEvent(time, tempo);
        }
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        for (Index i = 0; i < 4; i++) {
            this->poly[i]->processTransportEvent(time, state);
        }
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        for (Index i = 0; i < 4; i++) {
            this->poly[i]->processBeatTimeEvent(time, beattime);
        }
    }
}

void processTimeSignatureEvent(MillisecondTime time, Int numerator, Int denominator) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        for (Index i = 0; i < 4; i++) {
            this->poly[i]->processTimeSignatureEvent(time, numerator, denominator);
        }
    }
}

void processBBUEvent(MillisecondTime time, number bars, number beats, number units) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBBU(this->_currentTime, bars, beats, units, false)) {
        for (Index i = 0; i < 4; i++) {
            this->poly[i]->processBBUEvent(time, bars, beats, units);
        }
    }
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_07_getPresetValue(getSubState(preset, "MOD"));
    this->param_08_getPresetValue(getSubState(preset, "ATT"));
    this->param_09_getPresetValue(getSubState(preset, "DEC"));
    this->param_10_getPresetValue(getSubState(preset, "REL"));
    this->param_11_getPresetValue(getSubState(preset, "SUS"));
    this->param_12_getPresetValue(getSubState(preset, "METRO"));

    for (Index i = 0; i < 4; i++)
        this->poly[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "poly", i));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);

    for (Index i = 0; i < 4; i++)
        this->poly[i]->setPreset(time, getSubStateAt(getSubState(preset, "__sps"), "poly", i));

    this->param_07_setPresetValue(getSubState(preset, "MOD"));
    this->param_08_setPresetValue(getSubState(preset, "ATT"));
    this->param_09_setPresetValue(getSubState(preset, "DEC"));
    this->param_10_setPresetValue(getSubState(preset, "REL"));
    this->param_11_setPresetValue(getSubState(preset, "SUS"));
    this->param_12_setPresetValue(getSubState(preset, "METRO"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 0:
        {
        this->param_07_value_set(v);
        break;
        }
    case 1:
        {
        this->param_08_value_set(v);
        break;
        }
    case 2:
        {
        this->param_09_value_set(v);
        break;
        }
    case 3:
        {
        this->param_10_value_set(v);
        break;
        }
    case 4:
        {
        this->param_11_value_set(v);
        break;
        }
    case 5:
        {
        this->param_12_value_set(v);
        break;
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters())
            this->poly[0]->setPolyParameterValue(this->poly, index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_07_value;
        }
    case 1:
        {
        return this->param_08_value;
        }
    case 2:
        {
        return this->param_09_value;
        }
    case 3:
        {
        return this->param_10_value;
        }
    case 4:
        {
        return this->param_11_value;
        }
    case 5:
        {
        return this->param_12_value;
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters())
            return this->poly[0]->getPolyParameterValue(this->poly, index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 6 + this->poly[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "MOD";
        }
    case 1:
        {
        return "ATT";
        }
    case 2:
        {
        return "DEC";
        }
    case 3:
        {
        return "REL";
        }
    case 4:
        {
        return "SUS";
        }
    case 5:
        {
        return "METRO";
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterName(index);
            }
        }

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "MOD";
        }
    case 1:
        {
        return "ATT";
        }
    case 2:
        {
        return "DEC";
        }
    case 3:
        {
        return "REL";
        }
    case 4:
        {
        return "SUS";
        }
    case 5:
        {
        return "METRO";
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterId(index);
            }
        }

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 3000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 10000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 6;

            if (index < this->poly[0]->getNumParameters()) {
                for (Index i = 0; i < 4; i++) {
                    this->poly[i]->getParameterInfo(index, info);
                }
            }

            break;
            }
        }
    }
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 0) / (10 - 0);
            return normalizedValue;
        }
        }
    case 1:
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 3000 ? 3000 : value));
            ParameterValue normalizedValue = (value - 0) / (3000 - 0);
            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 10000 ? 10000 : value));
            ParameterValue normalizedValue = (value - 0) / (10000 - 0);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 4:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 0:
        {
        {
            {
                return 0 + value * (10 - 0);
            }
        }
        }
    case 1:
    case 2:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 3:
        {
        {
            {
                return 0 + value * (3000 - 0);
            }
        }
        }
    case 5:
        {
        {
            {
                return 0 + value * (10000 - 0);
            }
        }
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_07_value_constrain(value);
        }
    case 1:
        {
        return this->param_08_value_constrain(value);
        }
    case 2:
        {
        return this->param_09_value_constrain(value);
        }
    case 3:
        {
        return this->param_10_value_constrain(value);
        }
    case 4:
        {
        return this->param_11_value_constrain(value);
        }
    case 5:
        {
        return this->param_12_value_constrain(value);
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->constrainParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time, (ENGINE*)nullptr);

    for (Index i = 0; i < 4; i++) {
        this->poly[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time, (ENGINE*)nullptr);

    for (Index i = 0; i < 4; i++) {
        this->poly[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time, (ENGINE*)nullptr);

    for (Index i = 0; i < 4; i++) {
        this->poly[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->poly[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

class RNBOSubpatcher_28 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_28()
    {}
    
    ~RNBOSubpatcher_28()
    {
        deallocateSignals();
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time, (ENGINE*)nullptr);
        this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->ctlin_05_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->ctlin_06_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->p_02_perform(n);
        this->ip_01_perform(this->signals[0], n);
    
        this->adsr_01_perform(
            this->adsr_01_attack,
            this->adsr_01_decay,
            this->adsr_01_sustain,
            this->adsr_01_release,
            this->signals[0],
            this->signals[1],
            n
        );
    
        this->scopetilde_01_perform(this->signals[1], this->zeroBuffer, n);
        this->p_01_perform(this->signals[1], this->signals[0], n);
        this->signaladder_01_perform(this->signals[0], out2, out2, n);
        this->signaladder_02_perform(this->signals[0], out1, out1, n);
        this->p_03_perform(n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        RNBO_ASSERT(this->_isInitialized);
    
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
            this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
            this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->ip_01_dspsetup(forceDSPSetup);
        this->adsr_01_dspsetup(forceDSPSetup);
        this->scopetilde_01_dspsetup(forceDSPSetup);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->prepareToProcess(sampleRate, maxBlockSize, force);
        }
    
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processTempoEvent(time, tempo);
        }
    
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processTransportEvent(time, state);
        }
    
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processBeatTimeEvent(time, beattime);
        }
    
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
    }
    
    void processTimeSignatureEvent(MillisecondTime time, Int numerator, Int denominator) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processTimeSignatureEvent(time, numerator, denominator);
        }
    
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void processBBUEvent(MillisecondTime time, number bars, number beats, number units) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processBBUEvent(time, bars, beats, units);
        }
    
        this->p_02->processBBUEvent(time, bars, beats, units);
        this->p_03->processBBUEvent(time, bars, beats, units);
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++)
            this->p_01[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "test", i));
    
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "freq_calc"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "ratio_sequencer"));
    }
    
    void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
        for (Index i = 0; i < 4; i++)
            this->p_01[i]->setPreset(time, getSubStateAt(getSubState(preset, "__sps"), "test", i));
    
        this->p_02->setPreset(time, getSubState(getSubState(preset, "__sps"), "freq_calc"));
        this->p_03->setPreset(time, getSubState(getSubState(preset, "__sps"), "ratio_sequencer"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (index) {
        case 0:
            {
            this->param_01_value_set(v);
            break;
            }
        case 1:
            {
            this->param_02_value_set(v);
            break;
            }
        case 2:
            {
            this->param_03_value_set(v);
            break;
            }
        case 3:
            {
            this->param_04_value_set(v);
            break;
            }
        case 4:
            {
            this->param_05_value_set(v);
            break;
            }
        case 5:
            {
            this->param_06_value_set(v);
            break;
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters())
                this->p_01[0]->setPolyParameterValue(this->p_01, index, v, time);
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_01_value;
            }
        case 1:
            {
            return this->param_02_value;
            }
        case 2:
            {
            return this->param_03_value;
            }
        case 3:
            {
            return this->param_04_value;
            }
        case 4:
            {
            return this->param_05_value;
            }
        case 5:
            {
            return this->param_06_value;
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters())
                return this->p_01[0]->getPolyParameterValue(this->p_01, index);
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 6 + this->p_01[0]->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "MOD";
            }
        case 1:
            {
            return "ATT";
            }
        case 2:
            {
            return "DEC";
            }
        case 3:
            {
            return "REL";
            }
        case 4:
            {
            return "SUS";
            }
        case 5:
            {
            return "METRO";
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters()) {
                {
                    return this->p_01[0]->getParameterName(index);
                }
            }
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "poly/MOD";
            }
        case 1:
            {
            return "poly/ATT";
            }
        case 2:
            {
            return "poly/DEC";
            }
        case 3:
            {
            return "poly/REL";
            }
        case 4:
            {
            return "poly/SUS";
            }
        case 5:
            {
            return "poly/METRO";
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters()) {
                {
                    return this->p_01[0]->getParameterId(index);
                }
            }
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 100;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 100;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 3000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 5:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 10000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 6;
    
                if (index < this->p_01[0]->getNumParameters()) {
                    for (Index i = 0; i < 4; i++) {
                        this->p_01[i]->getParameterInfo(index, info);
                    }
                }
    
                index -= this->p_01[0]->getNumParameters();
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                index -= this->p_02->getNumParameters();
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 4:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 10 ? 10 : value));
                ParameterValue normalizedValue = (value - 0) / (10 - 0);
                return normalizedValue;
            }
            }
        case 1:
        case 2:
            {
            {
                value = (value < 0 ? 0 : (value > 100 ? 100 : value));
                ParameterValue normalizedValue = (value - 0) / (100 - 0);
                return normalizedValue;
            }
            }
        case 3:
            {
            {
                value = (value < 0 ? 0 : (value > 3000 ? 3000 : value));
                ParameterValue normalizedValue = (value - 0) / (3000 - 0);
                return normalizedValue;
            }
            }
        case 5:
            {
            {
                value = (value < 0 ? 0 : (value > 10000 ? 10000 : value));
                ParameterValue normalizedValue = (value - 0) / (10000 - 0);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters()) {
                {
                    return this->p_01[0]->convertToNormalizedParameterValue(index, value);
                }
            }
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 4:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 0:
            {
            {
                {
                    return 0 + value * (10 - 0);
                }
            }
            }
        case 1:
        case 2:
            {
            {
                {
                    return 0 + value * (100 - 0);
                }
            }
            }
        case 3:
            {
            {
                {
                    return 0 + value * (3000 - 0);
                }
            }
            }
        case 5:
            {
            {
                {
                    return 0 + value * (10000 - 0);
                }
            }
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters()) {
                {
                    return this->p_01[0]->convertFromNormalizedParameterValue(index, value);
                }
            }
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_01_value_constrain(value);
            }
        case 1:
            {
            return this->param_02_value_constrain(value);
            }
        case 2:
            {
            return this->param_03_value_constrain(value);
            }
        case 3:
            {
            return this->param_04_value_constrain(value);
            }
        case 4:
            {
            return this->param_05_value_constrain(value);
            }
        case 5:
            {
            return this->param_06_value_constrain(value);
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01[0]->getNumParameters()) {
                {
                    return this->p_01[0]->constrainParameterValue(index, value);
                }
            }
    
            index -= this->p_01[0]->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("poly/message_obj-21") == objectId)
                this->message_01_listin_number_set(payload);
    
            break;
            }
        }
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processNumMessage(tag, objectId, time, payload);
        }
    
        this->p_02->processNumMessage(tag, objectId, time, payload);
        this->p_03->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("poly/message_obj-21") == objectId)
                this->message_01_listin_list_set(payload);
    
            break;
            }
        }
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processListMessage(tag, objectId, time, payload);
        }
    
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("startupbang"):
            {
            if (TAG("poly/loadmess_obj-6") == objectId)
                this->loadmess_01_startupbang_bang();
    
            break;
            }
        case TAG("bangin"):
            {
            if (TAG("poly/button_obj-9") == objectId)
                this->button_03_bangin_bang();
    
            if (TAG("poly/button_obj-45") == objectId)
                this->button_04_bangin_bang();
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("poly/message_obj-21") == objectId)
                this->message_01_listin_bang_bang();
    
            break;
            }
        }
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processBangMessage(tag, objectId, time);
        }
    
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("poly/scope~_obj-89"):
            {
            return "poly/scope~_obj-89";
            }
        case TAG("monitor"):
            {
            return "monitor";
            }
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("poly/button_obj-9"):
            {
            return "poly/button_obj-9";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("poly/message_obj-21"):
            {
            return "poly/message_obj-21";
            }
        case TAG("poly/button_obj-45"):
            {
            return "poly/button_obj-45";
            }
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("poly/loadmess_obj-6"):
            {
            return "poly/loadmess_obj-6";
            }
        case TAG("bangin"):
            {
            return "bangin";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        }
    
        auto subpatchResult_0 = this->p_01[0]->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        if (index == 1) {
            this->mtof_01_innerMtoF_buffer = reInitDataView(
                this->mtof_01_innerMtoF_buffer,
                this->getPatcher()->RNBODefaultMtofLookupTable256
            );
        }
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->processDataViewUpdate(index, time);
        }
    
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        RNBO_ASSERT(!this->_isInitialized);
        this->assign_defaults();
        this->applyState();
        this->mtof_01_innerMtoF_buffer = new SampleBuffer(this->getPatcher()->RNBODefaultMtofLookupTable256);
        this->_isInitialized = true;
    }
    
    protected:
    
    class RNBOSubpatcher_25 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_28;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_25()
            {}
            
            ~RNBOSubpatcher_25()
            {
                deallocateSignals();
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in3 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
            
                if (this->getIsMuted())
                    return;
            
                this->cycle_tilde_02_perform(
                    this->cycle_tilde_02_frequency,
                    this->cycle_tilde_02_phase_offset,
                    this->signals[0],
                    this->dummyBuffer,
                    n
                );
            
                this->gen_01_perform(this->gen_01_in1, this->signals[1], n);
                this->dspexpr_02_perform(this->signals[0], this->signals[1], this->signals[2], n);
            
                this->cycle_tilde_01_perform(
                    this->cycle_tilde_01_frequency,
                    this->signals[2],
                    this->signals[1],
                    this->dummyBuffer,
                    n
                );
            
                this->dspexpr_01_perform(this->signals[1], in3, this->signals[2], n);
                this->signaladder_03_perform(this->signals[2], out1, out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                RNBO_ASSERT(this->_isInitialized);
            
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->cycle_tilde_02_dspsetup(forceDSPSetup);
                this->cycle_tilde_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setPreset(MillisecondTime , PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time, (ENGINE*)nullptr);
            
                if (index == 0) {
                    this->cycle_tilde_01_buffer = reInitDataView(
                        this->cycle_tilde_01_buffer,
                        this->getPatcher()->getPatcher()->RNBODefaultSinus
                    );
            
                    this->cycle_tilde_01_bufferUpdated();
            
                    this->cycle_tilde_02_buffer = reInitDataView(
                        this->cycle_tilde_02_buffer,
                        this->getPatcher()->getPatcher()->RNBODefaultSinus
                    );
            
                    this->cycle_tilde_02_bufferUpdated();
                }
            }
            
            void initialize() {
                RNBO_ASSERT(!this->_isInitialized);
                this->assign_defaults();
                this->applyState();
                this->cycle_tilde_01_buffer = new SampleBuffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                this->cycle_tilde_02_buffer = new SampleBuffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                this->_isInitialized = true;
            }
            
            protected:
            
            void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
            	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
            	getTopLevelPatcher()->processInternalEvents(time);
            	updateTime(time, (EXTERNALENGINE*)nullptr);
            }
            
            RNBOSubpatcher_25* operator->() {
                return this;
            }
            const RNBOSubpatcher_25* operator->() const {
                return this;
            }
            virtual RNBOSubpatcher_28* getPatcher() const {
                return static_cast<RNBOSubpatcher_28 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            MillisecondTime getPatcherTime() const {
                return this->_currentTime;
            }
            
            void eventinlet_01_out1_bang_bang() {}
            
            void eventinlet_01_out1_number_set(number v) {
                this->cycle_tilde_01_frequency_set(v);
            }
            
            template<typename LISTTYPE> void eventinlet_01_out1_list_set(const LISTTYPE& v) {
                {
                    if (v->length > 1)
                        this->cycle_tilde_01_phase_offset_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->cycle_tilde_01_frequency_set(converted);
                }
            }
            
            void eventinlet_02_out1_bang_bang() {}
            
            void eventinlet_02_out1_number_set(number v) {
                this->cycle_tilde_02_frequency_set(v);
            }
            
            template<typename LISTTYPE> void eventinlet_02_out1_list_set(const LISTTYPE& v) {
                {
                    if (v->length > 1)
                        this->cycle_tilde_02_phase_offset_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->cycle_tilde_02_frequency_set(converted);
                }
            }
            
            void eventinlet_03_out1_bang_bang() {}
            
            template<typename LISTTYPE> void eventinlet_03_out1_list_set(const LISTTYPE& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->gen_01_in1_set(converted);
                }
            }
            
            void deallocateSignals() {
                Index i;
            
                for (i = 0; i < 3; i++) {
                    this->signals[i] = freeSignal(this->signals[i]);
                }
            
                this->zeroBuffer = freeSignal(this->zeroBuffer);
                this->dummyBuffer = freeSignal(this->dummyBuffer);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            void setProbingTarget(MessageTag ) {}
            
            void initializeObjects() {}
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            void extractState(PatcherStateInterface& ) {}
            
            void applyState() {}
            
            ParameterValue getPolyParameterValue(RNBOSubpatcher_25* voices, ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return voices[0]->getParameterValue(index);
                    }
                }
            }
            
            void setPolyParameterValue(
                RNBOSubpatcher_25* voices,
                ParameterIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                switch (index) {
                default:
                    {
                    for (Index i = 0; i < 4; i++)
                        voices[i]->setParameterValue(index, value, time);
                    }
                }
            }
            
            void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time, (ENGINE*)nullptr);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void allocateDataRefs() {
                this->cycle_tilde_01_buffer->requestSize(16384, 1);
                this->cycle_tilde_01_buffer->setSampleRate(this->sr);
                this->cycle_tilde_02_buffer->requestSize(16384, 1);
                this->cycle_tilde_02_buffer->setSampleRate(this->sr);
                this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
                this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
            }
            
            void gen_01_in1_set(number v) {
                this->gen_01_in1 = v;
            }
            
            void eventinlet_03_out1_number_set(number v) {
                this->gen_01_in1_set(v);
            }
            
            void cycle_tilde_01_frequency_set(number v) {
                this->cycle_tilde_01_frequency = v;
            }
            
            void cycle_tilde_01_phase_offset_set(number v) {
                this->cycle_tilde_01_phase_offset = v;
            }
            
            void cycle_tilde_02_frequency_set(number v) {
                this->cycle_tilde_02_frequency = v;
            }
            
            void cycle_tilde_02_phase_offset_set(number v) {
                this->cycle_tilde_02_phase_offset = v;
            }
            
            void midiouthelper_midiout_set(number ) {}
            
            void cycle_tilde_02_perform(
                number frequency,
                number phase_offset,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(phase_offset);
                auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
                auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
                auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
                Index i;
            
                for (i = 0; i < (Index)n; i++) {
                    {
                        UInt32 uint_phase;
            
                        {
                            {
                                uint_phase = __cycle_tilde_02_phasei;
                            }
                        }
            
                        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
                        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                        number y0 = __cycle_tilde_02_buffer[(Index)idx];
                        number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                        number y = y0 + frac * (y1 - y0);
            
                        {
                            UInt32 pincr = (UInt32)(uint32_trunc(frequency * __cycle_tilde_02_f2i));
                            __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
                        }
            
                        out1[(Index)i] = y;
                        out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                        continue;
                    }
                }
            
                this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
            }
            
            void gen_01_perform(number in1, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < (Index)n; i++) {
                    out1[(Index)i] = in1 / (number)6.283185307179586;
                }
            }
            
            void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < (Index)n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void cycle_tilde_01_perform(
                number frequency,
                const Sample * phase_offset,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
                auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
                auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
                Index i;
            
                for (i = 0; i < (Index)n; i++) {
                    {
                        UInt32 uint_phase;
            
                        if (phase_offset[(Index)i] != 0 || 0 == 2) {
                            uint_phase = uint32_add(
                                uint32_trunc(phase_offset[(Index)i] * 4294967296.0),
                                __cycle_tilde_01_phasei
                            );
                        } else {
                            uint_phase = __cycle_tilde_01_phasei;
                        }
            
                        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
                        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                        number y0 = __cycle_tilde_01_buffer[(Index)idx];
                        number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                        number y = y0 + frac * (y1 - y0);
            
                        {
                            UInt32 pincr = (UInt32)(uint32_trunc(frequency * __cycle_tilde_01_f2i));
                            __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
                        }
            
                        out1[(Index)i] = y;
                        out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                        continue;
                    }
                }
            
                this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
            }
            
            void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < (Index)n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void signaladder_03_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < (Index)n; i++) {
                    out[(Index)i] = in1[(Index)i] + in2[(Index)i];
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number cycle_tilde_01_ph_next(number freq, number reset) {
                {
                    {
                        if (reset >= 0.)
                            this->cycle_tilde_01_ph_currentPhase = reset;
                    }
                }
            
                number pincr = freq * this->cycle_tilde_01_ph_conv;
            
                if (this->cycle_tilde_01_ph_currentPhase < 0.)
                    this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;
            
                if (this->cycle_tilde_01_ph_currentPhase > 1.)
                    this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;
            
                number tmp = this->cycle_tilde_01_ph_currentPhase;
                this->cycle_tilde_01_ph_currentPhase += pincr;
                return tmp;
            }
            
            void cycle_tilde_01_ph_reset() {
                this->cycle_tilde_01_ph_currentPhase = 0;
            }
            
            void cycle_tilde_01_ph_dspsetup() {
                this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
            }
            
            void cycle_tilde_01_dspsetup(bool force) {
                if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->cycle_tilde_01_phasei = 0;
                this->cycle_tilde_01_f2i = (number)4294967296 / this->sr;
                this->cycle_tilde_01_wrap = (Int)(this->cycle_tilde_01_buffer->getSize()) - 1;
                this->cycle_tilde_01_setupDone = true;
                this->cycle_tilde_01_ph_dspsetup();
            }
            
            void cycle_tilde_01_bufferUpdated() {
                this->cycle_tilde_01_wrap = (Int)(this->cycle_tilde_01_buffer->getSize()) - 1;
            }
            
            number cycle_tilde_02_ph_next(number freq, number reset) {
                {
                    {
                        if (reset >= 0.)
                            this->cycle_tilde_02_ph_currentPhase = reset;
                    }
                }
            
                number pincr = freq * this->cycle_tilde_02_ph_conv;
            
                if (this->cycle_tilde_02_ph_currentPhase < 0.)
                    this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;
            
                if (this->cycle_tilde_02_ph_currentPhase > 1.)
                    this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;
            
                number tmp = this->cycle_tilde_02_ph_currentPhase;
                this->cycle_tilde_02_ph_currentPhase += pincr;
                return tmp;
            }
            
            void cycle_tilde_02_ph_reset() {
                this->cycle_tilde_02_ph_currentPhase = 0;
            }
            
            void cycle_tilde_02_ph_dspsetup() {
                this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
            }
            
            void cycle_tilde_02_dspsetup(bool force) {
                if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->cycle_tilde_02_phasei = 0;
                this->cycle_tilde_02_f2i = (number)4294967296 / this->sr;
                this->cycle_tilde_02_wrap = (Int)(this->cycle_tilde_02_buffer->getSize()) - 1;
                this->cycle_tilde_02_setupDone = true;
                this->cycle_tilde_02_ph_dspsetup();
            }
            
            void cycle_tilde_02_bufferUpdated() {
                this->cycle_tilde_02_wrap = (Int)(this->cycle_tilde_02_buffer->getSize()) - 1;
            }
            
            void midiouthelper_sendMidi(number v) {
                this->midiouthelper_midiout_set(v);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                if (this->_voiceIndex == 1)
                    this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
                RNBO_UNUSED(inProcess);
                RNBO_UNUSED(engine);
                this->_currentTime = time;
                auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));
            
                if (offset >= (SampleIndex)(this->vs))
                    offset = (SampleIndex)(this->vs) - 1;
            
                if (offset < 0)
                    offset = 0;
            
                this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
            }
            
            void assign_defaults()
            {
                dspexpr_01_in1 = 0;
                dspexpr_01_in2 = 0;
                cycle_tilde_01_frequency = 0;
                cycle_tilde_01_phase_offset = 0;
                dspexpr_02_in1 = 0;
                dspexpr_02_in2 = 0;
                cycle_tilde_02_frequency = 0;
                cycle_tilde_02_phase_offset = 0;
                gen_01_in1 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.000022675736961451248;
                cycle_tilde_01_wrap = 0;
                cycle_tilde_01_ph_currentPhase = 0;
                cycle_tilde_01_ph_conv = 0;
                cycle_tilde_01_setupDone = false;
                cycle_tilde_02_wrap = 0;
                cycle_tilde_02_ph_currentPhase = 0;
                cycle_tilde_02_ph_conv = 0;
                cycle_tilde_02_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 0;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_01_in1;
                number dspexpr_01_in2;
                number cycle_tilde_01_frequency;
                number cycle_tilde_01_phase_offset;
                number dspexpr_02_in1;
                number dspexpr_02_in2;
                number cycle_tilde_02_frequency;
                number cycle_tilde_02_phase_offset;
                number gen_01_in1;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                Index sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[3];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                SampleBufferRef cycle_tilde_01_buffer;
                Int cycle_tilde_01_wrap;
                UInt32 cycle_tilde_01_phasei;
                SampleValue cycle_tilde_01_f2i;
                number cycle_tilde_01_ph_currentPhase;
                number cycle_tilde_01_ph_conv;
                bool cycle_tilde_01_setupDone;
                SampleBufferRef cycle_tilde_02_buffer;
                Int cycle_tilde_02_wrap;
                UInt32 cycle_tilde_02_phasei;
                SampleValue cycle_tilde_02_f2i;
                number cycle_tilde_02_ph_currentPhase;
                number cycle_tilde_02_ph_conv;
                bool cycle_tilde_02_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                bool _isInitialized = false;
    };
    
    class RNBOSubpatcher_26 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_28;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_26()
            {}
            
            ~RNBOSubpatcher_26()
            {
                deallocateSignals();
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                RNBO_ASSERT(this->_isInitialized);
            
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setPreset(MillisecondTime , PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                this->updateTime(time, (ENGINE*)nullptr);
            
                switch (tag) {
                case TAG("valin"):
                    {
                    if (TAG("poly/freq_calc/number_obj-20") == objectId)
                        this->numberobj_01_valin_set(payload);
            
                    if (TAG("poly/freq_calc/number_obj-12") == objectId)
                        this->numberobj_02_valin_set(payload);
            
                    break;
                    }
                case TAG("format"):
                    {
                    if (TAG("poly/freq_calc/number_obj-20") == objectId)
                        this->numberobj_01_format_set(payload);
            
                    if (TAG("poly/freq_calc/number_obj-12") == objectId)
                        this->numberobj_02_format_set(payload);
            
                    break;
                    }
                }
            }
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time, (ENGINE*)nullptr);
            
                switch (tag) {
                case TAG("bangin"):
                    {
                    if (TAG("poly/freq_calc/button_obj-18") == objectId)
                        this->button_01_bangin_bang();
            
                    if (TAG("poly/freq_calc/button_obj-22") == objectId)
                        this->button_02_bangin_bang();
            
                    break;
                    }
                }
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("bangout"):
                    {
                    return "bangout";
                    }
                case TAG("poly/freq_calc/button_obj-18"):
                    {
                    return "poly/freq_calc/button_obj-18";
                    }
                case TAG("poly/freq_calc/button_obj-22"):
                    {
                    return "poly/freq_calc/button_obj-22";
                    }
                case TAG("valout"):
                    {
                    return "valout";
                    }
                case TAG("poly/freq_calc/number_obj-20"):
                    {
                    return "poly/freq_calc/number_obj-20";
                    }
                case TAG("setup"):
                    {
                    return "setup";
                    }
                case TAG("poly/freq_calc/number_obj-12"):
                    {
                    return "poly/freq_calc/number_obj-12";
                    }
                case TAG("bangin"):
                    {
                    return "bangin";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                case TAG("format"):
                    {
                    return "format";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                RNBO_ASSERT(!this->_isInitialized);
                this->assign_defaults();
                this->applyState();
                this->_isInitialized = true;
            }
            
            protected:
            
            void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
            	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
            	getTopLevelPatcher()->processInternalEvents(time);
            	updateTime(time, (EXTERNALENGINE*)nullptr);
            }
            
            RNBOSubpatcher_26* operator->() {
                return this;
            }
            const RNBOSubpatcher_26* operator->() const {
                return this;
            }
            virtual RNBOSubpatcher_28* getPatcher() const {
                return static_cast<RNBOSubpatcher_28 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number safediv(number num, number denom) {
                return (denom == 0.0 ? 0.0 : num / denom);
            }
            
            number safepow(number base, number exponent) {
                return fixnan(rnbo_pow(base, exponent));
            }
            
            number scale(
                number x,
                number lowin,
                number hiin,
                number lowout,
                number highout,
                number pow
            ) {
                auto inscale = this->safediv(1., hiin - lowin);
                number outdiff = highout - lowout;
                number value = (x - lowin) * inscale;
            
                if (pow != 1) {
                    if (value > 0)
                        value = this->safepow(value, pow);
                    else
                        value = -this->safepow(-value, pow);
                }
            
                value = value * outdiff + lowout;
                return value;
            }
            
            Index voice() {
                return this->_voiceIndex;
            }
            
            number random(number low, number high) {
                number range = high - low;
                return globalrandom() * range + low;
            }
            
            MillisecondTime getPatcherTime() const {
                return this->_currentTime;
            }
            
            void eventinlet_04_out1_bang_bang() {
                this->pak_01_in1_bang_bang();
            }
            
            template<typename LISTTYPE> void eventinlet_04_out1_list_set(const LISTTYPE& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->pak_01_in1_number_set(converted);
                }
            }
            
            void button_01_bangin_bang() {
                this->button_01_bangval_bang();
            }
            
            void eventinlet_05_out1_bang_bang() {
                this->pak_02_in1_bang_bang();
            }
            
            template<typename LISTTYPE> void eventinlet_05_out1_list_set(const LISTTYPE& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->pak_02_in1_number_set(converted);
                }
            }
            
            void eventinlet_06_out1_bang_bang() {
                this->counter_01_input_bang();
            }
            
            void eventinlet_06_out1_number_set(number v) {
                RNBO_UNUSED(v);
                this->counter_01_input_bang();
            }
            
            template<typename LISTTYPE> void eventinlet_06_out1_list_set(const LISTTYPE& v) {
                RNBO_UNUSED(v);
                this->counter_01_input_bang();
            }
            
            void button_02_bangin_bang() {
                this->button_02_bangval_bang();
            }
            
            void numberobj_01_valin_set(number v) {
                this->numberobj_01_value_set(v);
            }
            
            void numberobj_01_format_set(number v) {
                this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void numberobj_02_valin_set(number v) {
                this->numberobj_02_value_set(v);
            }
            
            void numberobj_02_format_set(number v) {
                this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void deallocateSignals() {
                Index i;
                this->zeroBuffer = freeSignal(this->zeroBuffer);
                this->dummyBuffer = freeSignal(this->dummyBuffer);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            void setProbingTarget(MessageTag ) {}
            
            void initializeObjects() {
                this->random_01_nz_init();
                this->random_02_nz_init();
                this->numberobj_01_init();
                this->numberobj_02_init();
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            void extractState(PatcherStateInterface& ) {}
            
            void applyState() {}
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time, (ENGINE*)nullptr);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void allocateDataRefs() {}
            
            void pack_02_in2_set(number v) {
                this->pack_02_data[1] = v;
            }
            
            void expr_02_out1_set(number v) {
                this->expr_02_out1 = v;
                this->pack_02_in2_set(this->expr_02_out1);
            }
            
            void expr_02_in1_set(number in1) {
                this->expr_02_in1 = in1;
                this->expr_02_out1_set(this->expr_02_in1 * this->expr_02_in2);//#map:freq_calc/*_obj-71:1
            }
            
            void expr_02_in2_set(number v) {
                this->expr_02_in2 = v;
            }
            
            template<typename LISTTYPE> void pak_02_out_set(const LISTTYPE& v) {
                {
                    if (v->length > 1)
                        this->expr_02_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_02_in1_set(converted);
                }
            }
            
            void pak_02_in1_number_set(number v) {
                this->pak_02_data[0] = v;
                this->pak_02_out_set(this->pak_02_data);
            }
            
            void eventinlet_05_out1_number_set(number v) {
                this->pak_02_in1_number_set(v);
            }
            
            void pack_01_in2_set(number v) {
                this->pack_01_data[1] = v;
            }
            
            void expr_01_out1_set(number v) {
                this->expr_01_out1 = v;
                this->pack_01_in2_set(this->expr_01_out1);
            }
            
            void expr_01_in1_set(number in1) {
                this->expr_01_in1 = in1;
                this->expr_01_out1_set(this->expr_01_in1 * this->expr_01_in2);//#map:freq_calc/*_obj-68:1
            }
            
            void expr_01_in2_set(number v) {
                this->expr_01_in2 = v;
            }
            
            template<typename LISTTYPE> void pak_01_out_set(const LISTTYPE& v) {
                {
                    if (v->length > 1)
                        this->expr_01_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_01_in1_set(converted);
                }
            }
            
            void pak_01_in1_number_set(number v) {
                this->pak_01_data[0] = v;
                this->pak_01_out_set(this->pak_01_data);
            }
            
            void eventinlet_04_out1_number_set(number v) {
                this->pak_01_in1_number_set(v);
            }
            
            void pak_01_in1_bang_bang() {
                this->pak_01_out_set(this->pak_01_data);
            }
            
            void pak_02_in2_number_set(number v) {
                this->pak_02_data[1] = v;
                this->pak_02_out_set(this->pak_02_data);
            }
            
            template<typename LISTTYPE> void scale_02_out_set(const LISTTYPE& v) {
                this->scale_02_out = jsCreateListCopy(v);
            
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->pak_02_in2_number_set(converted);
                }
            }
            
            template<typename LISTTYPE> void scale_02_input_set(const LISTTYPE& v) {
                this->scale_02_input = jsCreateListCopy(v);
                list tmp = {};
            
                for (Index i = 0; i < v->length; i++) {
                    tmp->push(this->scale(
                        v[(Index)i],
                        this->scale_02_inlow,
                        this->scale_02_inhigh,
                        this->scale_02_outlow,
                        this->scale_02_outhigh,
                        this->scale_02_power
                    ));
                }
            
                this->scale_02_out_set(tmp);
            }
            
            void random_02_result_set(number v) {
                {
                    listbase<number, 1> converted = {v};
                    this->scale_02_input_set(converted);
                }
            }
            
            void random_02_trigger_bang() {
                this->random_02_result_set(rnbo_abs(this->random_02_nz_next()) * this->random_02_limit);
            }
            
            void numberobj_02_output_set(number ) {}
            
            void numberobj_02_value_set(number v) {
                this->numberobj_02_value_setter(v);
                v = this->numberobj_02_value;
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_02_output_set(localvalue);
            }
            
            void pak_01_in2_number_set(number v) {
                this->pak_01_data[1] = v;
                this->pak_01_out_set(this->pak_01_data);
            }
            
            template<typename LISTTYPE> void scale_01_out_set(const LISTTYPE& v) {
                this->scale_01_out = jsCreateListCopy(v);
            
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->pak_01_in2_number_set(converted);
                }
            }
            
            template<typename LISTTYPE> void scale_01_input_set(const LISTTYPE& v) {
                this->scale_01_input = jsCreateListCopy(v);
                list tmp = {};
            
                for (Index i = 0; i < v->length; i++) {
                    tmp->push(this->scale(
                        v[(Index)i],
                        this->scale_01_inlow,
                        this->scale_01_inhigh,
                        this->scale_01_outlow,
                        this->scale_01_outhigh,
                        this->scale_01_power
                    ));
                }
            
                this->scale_01_out_set(tmp);
            }
            
            void random_01_result_set(number v) {
                this->numberobj_02_value_set(v);
            
                {
                    listbase<number, 1> converted = {v};
                    this->scale_01_input_set(converted);
                }
            }
            
            void random_01_trigger_bang() {
                this->random_01_result_set(rnbo_abs(this->random_01_nz_next()) * this->random_01_limit);
            }
            
            void trigger_01_out4_bang() {
                this->random_02_trigger_bang();
                this->random_01_trigger_bang();
            }
            
            void eventoutlet_03_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime, (ENGINE*)nullptr);
                this->getPatcher()->p_02_out3_number_set(v);
            }
            
            template<typename LISTTYPE> void eventoutlet_02_in1_list_set(const LISTTYPE& v) {
                this->getPatcher()->updateTime(this->_currentTime, (ENGINE*)nullptr);
                this->getPatcher()->p_02_out2_list_set((list)v);
            }
            
            template<typename LISTTYPE> void pack_02_out_set(const LISTTYPE& v) {
                this->eventoutlet_02_in1_list_set(v);
            }
            
            void pack_02_in1_number_set(number v) {
                this->pack_02_data[0] = v;
                this->pack_02_out_set(this->pack_02_data);
            }
            
            template<typename LISTTYPE> void eventoutlet_01_in1_list_set(const LISTTYPE& v) {
                this->getPatcher()->updateTime(this->_currentTime, (ENGINE*)nullptr);
                this->getPatcher()->p_02_out1_list_set((list)v);
            }
            
            template<typename LISTTYPE> void pack_01_out_set(const LISTTYPE& v) {
                this->eventoutlet_01_in1_list_set(v);
            }
            
            void pack_01_in1_number_set(number v) {
                this->pack_01_data[0] = v;
                this->pack_01_out_set(this->pack_01_data);
            }
            
            void trigger_01_out3_set(number v) {
                this->eventoutlet_03_in1_number_set(v);
                this->pack_02_in1_number_set(v);
                this->pack_01_in1_number_set(v);
            }
            
            void button_02_output_bang() {}
            
            void button_02_bangval_bang() {
                ;
                this->button_02_output_bang();
            }
            
            void trigger_01_out2_bang() {
                this->button_02_bangval_bang();
                this->random_02_trigger_bang();
                this->random_01_trigger_bang();
            }
            
            void expr_03_out1_set(number v) {
                this->expr_03_out1 = v;
                this->pack_02_in1_number_set(this->expr_03_out1);
                this->pack_01_in1_number_set(this->expr_03_out1);
            }
            
            void expr_03_in1_set(number in1) {
                this->expr_03_in1 = in1;
                this->expr_03_out1_set(this->expr_03_in1 - this->expr_03_in2);//#map:freq_calc/-_obj-61:1
            }
            
            void trigger_01_out1_set(number v) {
                this->eventoutlet_03_in1_number_set(v);
                this->expr_03_in1_set(v);
            }
            
            void trigger_01_input_number_set(number v) {
                this->trigger_01_out4_bang();
                this->trigger_01_out3_set(trunc(v));
                this->trigger_01_out2_bang();
                this->trigger_01_out1_set(trunc(v));
            }
            
            void expr_04_out1_set(number v) {
                this->expr_04_out1 = v;
                this->trigger_01_input_number_set(this->expr_04_out1);
            }
            
            void expr_04_in1_set(number in1) {
                this->expr_04_in1 = in1;
                this->expr_04_out1_set(this->expr_04_in1 * this->expr_04_in2);//#map:freq_calc/*_obj-60:1
            }
            
            void counter_01_output_set(number v) {
                this->counter_01_output = v;
                this->expr_04_in1_set(v);
            }
            
            void counter_01_overflow_bang_bang() {}
            
            number counter_01_overflow_number_constrain(number v) const {
                if (v < 0)
                    v = 0;
            
                if (v > 1)
                    v = 1;
            
                return v;
            }
            
            void counter_01_overflow_number_set(number v) {
                v = this->counter_01_overflow_number_constrain(v);
                this->counter_01_overflow_number = v;
            }
            
            void counter_01_carry_set(number v) {
                this->counter_01_carry = v;
            }
            
            void counter_01_underflow_bang_bang() {}
            
            number counter_01_underflow_number_constrain(number v) const {
                if (v < 0)
                    v = 0;
            
                if (v > 1)
                    v = 1;
            
                return v;
            }
            
            void counter_01_underflow_number_set(number v) {
                v = this->counter_01_underflow_number_constrain(v);
                this->counter_01_underflow_number = v;
            }
            
            void counter_01_input_bang() {
                this->counter_01_output_set(this->counter_01_count);
                this->counter_01_inc();
            
                if (this->counter_01_count > this->counter_01_maximum) {
                    if (this->counter_01_direction == 2) {
                        this->counter_01_phase = !(bool)(this->counter_01_phase);
                        this->counter_01_count = this->counter_01_maximum;
                        this->counter_01_inc();
                    } else
                        this->counter_01_count = this->counter_01_minimum;
            
                    if ((bool)(!(bool)(this->counter_01_overflow_number))) {
                        if (this->counter_01_carryflag == 1)
                            this->counter_01_overflow_bang_bang();
                        else
                            this->counter_01_overflow_number_set(1);
                    }
            
                    this->counter_01_carry_set(this->counter_01_carry + 1);
                } else if ((bool)(this->counter_01_overflow_number) && this->counter_01_carryflag == 0)
                    this->counter_01_overflow_number_set(0);
            
                if (this->counter_01_count < this->counter_01_minimum) {
                    if (this->counter_01_direction == 2) {
                        this->counter_01_phase = !(bool)(this->counter_01_phase);
                        this->counter_01_count = this->counter_01_minimum;
                        this->counter_01_inc();
                    } else
                        this->counter_01_count = this->counter_01_maximum;
            
                    if ((bool)(!(bool)(this->counter_01_underflow_number))) {
                        if (this->counter_01_carryflag == 1)
                            this->counter_01_underflow_bang_bang();
                        else
                            this->counter_01_underflow_number_set(1);
                    }
            
                    this->counter_01_carry_set(this->counter_01_carry + 1);
                } else if ((bool)(this->counter_01_underflow_number) && this->counter_01_carryflag == 0)
                    this->counter_01_underflow_number_set(0);
            }
            
            void button_01_output_bang() {
                this->counter_01_input_bang();
            }
            
            void button_01_bangval_bang() {
                ;
                this->button_01_output_bang();
            }
            
            void pak_02_in1_bang_bang() {
                this->pak_02_out_set(this->pak_02_data);
            }
            
            void numberobj_01_output_set(number ) {}
            
            void numberobj_01_value_set(number v) {
                this->numberobj_01_value_setter(v);
                v = this->numberobj_01_value;
                number localvalue = v;
            
                if (this->numberobj_01_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_01_output_set(localvalue);
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void random_01_limit_setter(number v) {
                if (v >= 0)
                    this->random_01_limit = v;
            }
            
            void random_02_limit_setter(number v) {
                if (v >= 0)
                    this->random_02_limit = v;
            }
            
            void numberobj_01_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_01_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_01_value = localvalue;
            }
            
            void numberobj_02_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_02_value = localvalue;
            }
            
            void random_01_nz_reset() {
                xoshiro_reset(
                    systemticks() + this->voice() + this->random(0, 10000),
                    this->random_01_nz_state
                );
            }
            
            void random_01_nz_init() {
                this->random_01_nz_reset();
            }
            
            void random_01_nz_seed(number v) {
                xoshiro_reset(v, this->random_01_nz_state);
            }
            
            number random_01_nz_next() {
                return xoshiro_next(this->random_01_nz_state);
            }
            
            void random_02_nz_reset() {
                xoshiro_reset(
                    systemticks() + this->voice() + this->random(0, 10000),
                    this->random_02_nz_state
                );
            }
            
            void random_02_nz_init() {
                this->random_02_nz_reset();
            }
            
            void random_02_nz_seed(number v) {
                xoshiro_reset(v, this->random_02_nz_state);
            }
            
            number random_02_nz_next() {
                return xoshiro_next(this->random_02_nz_state);
            }
            
            void counter_01_inc() {
                this->counter_01_count = ((bool)(this->counter_01_phase) ? this->counter_01_count + 1 : this->counter_01_count - 1);
            }
            
            void numberobj_01_init() {
                this->numberobj_01_currentFormat = 6;
            }
            
            void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_01_value;
            }
            
            void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_01_value_set(preset["value"]);
            }
            
            void numberobj_02_init() {
                this->numberobj_02_currentFormat = 6;
            }
            
            void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_02_value;
            }
            
            void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_02_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
                RNBO_UNUSED(inProcess);
                RNBO_UNUSED(engine);
                this->_currentTime = time;
                auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));
            
                if (offset >= (SampleIndex)(this->vs))
                    offset = (SampleIndex)(this->vs) - 1;
            
                if (offset < 0)
                    offset = 0;
            
                this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
            }
            
            void assign_defaults()
            {
                expr_01_in1 = 0;
                expr_01_in2 = 1;
                expr_01_out1 = 0;
                scale_01_inlow = 0;
                scale_01_inhigh = 1;
                scale_01_outlow = 0.99;
                scale_01_outhigh = 1.01;
                scale_01_power = 1;
                random_01_limit = 1;
                random_01_limit_setter(random_01_limit);
                random_01_seed = 0;
                expr_02_in1 = 0;
                expr_02_in2 = 1;
                expr_02_out1 = 0;
                scale_02_inlow = 0;
                scale_02_inhigh = 1;
                scale_02_outlow = 0.99;
                scale_02_outhigh = 1.01;
                scale_02_power = 1;
                random_02_limit = 1;
                random_02_limit_setter(random_02_limit);
                random_02_seed = 0;
                expr_03_in1 = 0;
                expr_03_in2 = 1;
                expr_03_out1 = 0;
                expr_04_in1 = 0;
                expr_04_in2 = 2;
                expr_04_out1 = 0;
                counter_01_carryflag = 0;
                counter_01_direction = 0;
                counter_01_resetnext_number = 0;
                counter_01_resetnow_number = 0;
                counter_01_maximum = 2;
                counter_01_output = 0;
                counter_01_underflow_number = 0;
                counter_01_overflow_number = 0;
                counter_01_carry = 0;
                counter_01_minimum = 1;
                numberobj_01_value = 0;
                numberobj_01_value_setter(numberobj_01_value);
                numberobj_02_value = 0;
                numberobj_02_value_setter(numberobj_02_value);
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.000022675736961451248;
                pack_01_data = { 0, 0 };
                pak_01_data = { 0, 0 };
                pack_02_data = { 0, 0 };
                pak_02_data = { 0, 0 };
                counter_01_count = 1;
                counter_01_phase = true;
                numberobj_01_currentFormat = 6;
                numberobj_01_lastValue = 0;
                numberobj_02_currentFormat = 6;
                numberobj_02_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_01_in1;
                number expr_01_in2;
                number expr_01_out1;
                list scale_01_input;
                number scale_01_inlow;
                number scale_01_inhigh;
                number scale_01_outlow;
                number scale_01_outhigh;
                number scale_01_power;
                list scale_01_out;
                number random_01_limit;
                number random_01_seed;
                number expr_02_in1;
                number expr_02_in2;
                number expr_02_out1;
                list scale_02_input;
                number scale_02_inlow;
                number scale_02_inhigh;
                number scale_02_outlow;
                number scale_02_outhigh;
                number scale_02_power;
                list scale_02_out;
                number random_02_limit;
                number random_02_seed;
                number expr_03_in1;
                number expr_03_in2;
                number expr_03_out1;
                number expr_04_in1;
                number expr_04_in2;
                number expr_04_out1;
                Int counter_01_carryflag;
                number counter_01_direction;
                number counter_01_resetnext_number;
                number counter_01_resetnow_number;
                number counter_01_maximum;
                number counter_01_output;
                number counter_01_underflow_number;
                number counter_01_overflow_number;
                number counter_01_carry;
                number counter_01_minimum;
                number numberobj_01_value;
                number numberobj_02_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                Index sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                list pack_01_data;
                list pak_01_data;
                UInt random_01_nz_state[4] = { };
                list pack_02_data;
                list pak_02_data;
                UInt random_02_nz_state[4] = { };
                number counter_01_count;
                bool counter_01_phase;
                Int numberobj_01_currentFormat;
                number numberobj_01_lastValue;
                Int numberobj_02_currentFormat;
                number numberobj_02_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                bool _isInitialized = false;
    };
    
    class RNBOSubpatcher_27 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_28;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_27()
            {}
            
            ~RNBOSubpatcher_27()
            {
                deallocateSignals();
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                RNBO_ASSERT(this->_isInitialized);
            
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime time, TransportState state) {
                this->updateTime(time, (ENGINE*)nullptr);
                this->metro_01_onTransportChanged(state);
            }
            
            void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
                this->updateTime(time, (ENGINE*)nullptr);
                this->metro_01_onBeatTimeChanged(beattime);
            }
            
            void processTimeSignatureEvent(MillisecondTime , Int , Int ) {}
            
            void processBBUEvent(MillisecondTime , number , number , number ) {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setPreset(MillisecondTime , PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                RNBO_ASSERT(!this->_isInitialized);
                this->assign_defaults();
                this->applyState();
                this->_isInitialized = true;
            }
            
            protected:
            
            void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
            	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
            	getTopLevelPatcher()->processInternalEvents(time);
            	updateTime(time, (EXTERNALENGINE*)nullptr);
            }
            
            RNBOSubpatcher_27* operator->() {
                return this;
            }
            const RNBOSubpatcher_27* operator->() const {
                return this;
            }
            virtual RNBOSubpatcher_28* getPatcher() const {
                return static_cast<RNBOSubpatcher_28 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, 1935387534, false);
            }
            
            MillisecondTime getPatcherTime() const {
                return this->_currentTime;
            }
            
            void eventinlet_07_out1_bang_bang() {
                this->metro_01_on_bang();
            }
            
            void eventinlet_07_out1_number_set(number v) {
                this->metro_01_on_set(v);
            }
            
            void metro_01_tick_bang() {
                this->metro_01_tickout_bang();
                this->getEngine()->flushClockEvents(this, 1935387534, false);;
            
                if ((bool)(this->metro_01_on)) {
                    this->metro_01_last = this->_currentTime;
            
                    {
                        this->metro_01_next = this->metro_01_last + this->metro_01_interval;
                        this->getEngine()->scheduleClockEvent(this, 1935387534, this->metro_01_interval + this->_currentTime);;
                    }
                }
            }
            
            void eventinlet_08_out1_bang_bang() {
                this->metro_01_interval_bang();
            }
            
            template<typename LISTTYPE> void eventinlet_08_out1_list_set(const LISTTYPE& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->metro_01_interval_set(converted);
                }
            }
            
            void eventinlet_09_out1_number_set(number v) {
                this->counter_02_resetnext_number_set(v);
            }
            
            template<typename LISTTYPE> void eventinlet_09_out1_list_set(const LISTTYPE& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->counter_02_resetnext_number_set(converted);
                }
            }
            
            void deallocateSignals() {
                Index i;
                this->zeroBuffer = freeSignal(this->zeroBuffer);
                this->dummyBuffer = freeSignal(this->dummyBuffer);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            void setProbingTarget(MessageTag ) {}
            
            void initializeObjects() {
                this->codebox_01_init();
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            void extractState(PatcherStateInterface& ) {}
            
            void applyState() {}
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time, (ENGINE*)nullptr);
            
                switch (index) {
                case 1935387534:
                    {
                    this->metro_01_tick_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time, (ENGINE*)nullptr);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
            
                if ((bool)(this->metro_01_on))
                    this->metro_01_on_set(1);
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void allocateDataRefs() {}
            
            void metro_01_on_set(number v) {
                this->metro_01_on = v;
                this->getEngine()->flushClockEvents(this, 1935387534, false);;
            
                if ((bool)(v)) {
                    {
                        this->getEngine()->scheduleClockEvent(this, 1935387534, 0 + this->_currentTime);;
                    }
                }
            }
            
            void metro_01_interval_set(number v) {
                this->metro_01_interval_setter(v);
                v = this->metro_01_interval;
            }
            
            template<typename LISTTYPE> void eventinlet_07_out1_list_set(const LISTTYPE& v) {
                {
                    if (v->length > 1)
                        this->metro_01_interval_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->metro_01_on_set(converted);
                }
            }
            
            void eventinlet_08_out1_number_set(number v) {
                this->metro_01_interval_set(v);
            }
            
            void counter_02_resetnext_bang_bang() {
                this->counter_02_count = this->counter_02_minimum;
            }
            
            void eventinlet_09_out1_bang_bang() {
                this->counter_02_resetnext_bang_bang();
            }
            
            void metro_01_on_bang() {
                number v = this->metro_01_on;
                this->getEngine()->flushClockEvents(this, 1935387534, false);;
            
                if ((bool)(v)) {
                    {
                        this->getEngine()->scheduleClockEvent(this, 1935387534, 0 + this->_currentTime);;
                    }
                }
            }
            
            template<typename LISTTYPE> void eventoutlet_04_in1_list_set(const LISTTYPE& v) {
                this->getPatcher()->updateTime(this->_currentTime, (ENGINE*)nullptr);
                this->getPatcher()->p_03_out1_list_set((list)v);
            }
            
            template<typename LISTTYPE> void codebox_01_out1_set(const LISTTYPE& v) {
                this->codebox_01_out1 = jsCreateListCopy(v);
                this->eventoutlet_04_in1_list_set(this->codebox_01_out1);
            }
            
            void codebox_01_in1_set(number in1) {
                this->codebox_01_in1 = in1;
                this->codebox_01_out1_set(this->codebox_01_result(this->codebox_01_in1));//#map:ratio_sequencer/codebox_obj-3:37
            }
            
            void counter_02_output_set(number v) {
                this->counter_02_output = v;
                this->codebox_01_in1_set(v);
            }
            
            void counter_02_overflow_bang_bang() {}
            
            number counter_02_overflow_number_constrain(number v) const {
                if (v < 0)
                    v = 0;
            
                if (v > 1)
                    v = 1;
            
                return v;
            }
            
            void counter_02_overflow_number_set(number v) {
                v = this->counter_02_overflow_number_constrain(v);
                this->counter_02_overflow_number = v;
            }
            
            void counter_02_carry_set(number v) {
                this->counter_02_carry = v;
            }
            
            void counter_02_underflow_bang_bang() {}
            
            number counter_02_underflow_number_constrain(number v) const {
                if (v < 0)
                    v = 0;
            
                if (v > 1)
                    v = 1;
            
                return v;
            }
            
            void counter_02_underflow_number_set(number v) {
                v = this->counter_02_underflow_number_constrain(v);
                this->counter_02_underflow_number = v;
            }
            
            void counter_02_input_bang() {
                this->counter_02_output_set(this->counter_02_count);
                this->counter_02_inc();
            
                if (this->counter_02_count > this->counter_02_maximum) {
                    if (this->counter_02_direction == 2) {
                        this->counter_02_phase = !(bool)(this->counter_02_phase);
                        this->counter_02_count = this->counter_02_maximum;
                        this->counter_02_inc();
                    } else
                        this->counter_02_count = this->counter_02_minimum;
            
                    if ((bool)(!(bool)(this->counter_02_overflow_number))) {
                        if (this->counter_02_carryflag == 1)
                            this->counter_02_overflow_bang_bang();
                        else
                            this->counter_02_overflow_number_set(1);
                    }
            
                    this->counter_02_carry_set(this->counter_02_carry + 1);
                } else if ((bool)(this->counter_02_overflow_number) && this->counter_02_carryflag == 0)
                    this->counter_02_overflow_number_set(0);
            
                if (this->counter_02_count < this->counter_02_minimum) {
                    if (this->counter_02_direction == 2) {
                        this->counter_02_phase = !(bool)(this->counter_02_phase);
                        this->counter_02_count = this->counter_02_minimum;
                        this->counter_02_inc();
                    } else
                        this->counter_02_count = this->counter_02_maximum;
            
                    if ((bool)(!(bool)(this->counter_02_underflow_number))) {
                        if (this->counter_02_carryflag == 1)
                            this->counter_02_underflow_bang_bang();
                        else
                            this->counter_02_underflow_number_set(1);
                    }
            
                    this->counter_02_carry_set(this->counter_02_carry + 1);
                } else if ((bool)(this->counter_02_underflow_number) && this->counter_02_carryflag == 0)
                    this->counter_02_underflow_number_set(0);
            }
            
            void metro_01_tickout_bang() {
                this->counter_02_input_bang();
            }
            
            void metro_01_interval_bang() {}
            
            void counter_02_resetnext_number_set(number v) {
                this->counter_02_resetnext_number = v;
                this->counter_02_count = v;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void metro_01_interval_setter(number v) {
                this->metro_01_interval = (v > 0 ? v : 0);
            }
            
            void codebox_01_init() {
                this->codebox_01_lookup[0][0] = 1;//#map:_###_obj_###_:6
                this->codebox_01_lookup[0][1] = 2;//#map:_###_obj_###_:6
                this->codebox_01_lookup[1][0] = 3;//#map:_###_obj_###_:7
                this->codebox_01_lookup[1][1] = 8;//#map:_###_obj_###_:7
                this->codebox_01_lookup[2][0] = 1;//#map:_###_obj_###_:8
                this->codebox_01_lookup[2][1] = 2;//#map:_###_obj_###_:8
                this->codebox_01_lookup[3][0] = 1;//#map:_###_obj_###_:9
                this->codebox_01_lookup[3][1] = 3;//#map:_###_obj_###_:9
                this->codebox_01_lookup[4][0] = 4;//#map:_###_obj_###_:10
                this->codebox_01_lookup[4][1] = 9;//#map:_###_obj_###_:10
                this->codebox_01_lookup[5][0] = 1;//#map:_###_obj_###_:11
                this->codebox_01_lookup[5][1] = 3;//#map:_###_obj_###_:11
                this->codebox_01_lookup[6][0] = 1;//#map:_###_obj_###_:12
                this->codebox_01_lookup[6][1] = 4;//#map:_###_obj_###_:12
                this->codebox_01_lookup[7][0] = 3;//#map:_###_obj_###_:13
                this->codebox_01_lookup[7][1] = 8;//#map:_###_obj_###_:13
                this->codebox_01_lookup[8][0] = 1;//#map:_###_obj_###_:14
                this->codebox_01_lookup[8][1] = 4;//#map:_###_obj_###_:14
                this->codebox_01_lookup[9][0] = 1;//#map:_###_obj_###_:15
                this->codebox_01_lookup[9][1] = 5;//#map:_###_obj_###_:15
                this->codebox_01_lookup[10][0] = 2;//#map:_###_obj_###_:16
                this->codebox_01_lookup[10][1] = 5;//#map:_###_obj_###_:16
                this->codebox_01_lookup[11][0] = 1;//#map:_###_obj_###_:17
                this->codebox_01_lookup[11][1] = 5;//#map:_###_obj_###_:17
                this->codebox_01_lookup[12][0] = 1;//#map:_###_obj_###_:18
                this->codebox_01_lookup[12][1] = 6;//#map:_###_obj_###_:18
                this->codebox_01_lookup[13][0] = 1;//#map:_###_obj_###_:19
                this->codebox_01_lookup[13][1] = 7;//#map:_###_obj_###_:19
                this->codebox_01_lookup[14][0] = 2;//#map:_###_obj_###_:20
                this->codebox_01_lookup[14][1] = 7;//#map:_###_obj_###_:20
                this->codebox_01_lookup[15][0] = 1;//#map:_###_obj_###_:21
                this->codebox_01_lookup[15][1] = 7;//#map:_###_obj_###_:21
                this->codebox_01_lookup[16][0] = 1;//#map:_###_obj_###_:22
                this->codebox_01_lookup[16][1] = 8;//#map:_###_obj_###_:22
                this->codebox_01_lookup[17][0] = 3;//#map:_###_obj_###_:23
                this->codebox_01_lookup[17][1] = 8;//#map:_###_obj_###_:23
                this->codebox_01_lookup[18][0] = 1;//#map:_###_obj_###_:24
                this->codebox_01_lookup[18][1] = 8;//#map:_###_obj_###_:24
                this->codebox_01_lookup[19][0] = 1;//#map:_###_obj_###_:25
                this->codebox_01_lookup[19][1] = 9;//#map:_###_obj_###_:25
                this->codebox_01_lookup[20][0] = 2;//#map:_###_obj_###_:26
                this->codebox_01_lookup[20][1] = 9;//#map:_###_obj_###_:26
                this->codebox_01_lookup[21][0] = 1;//#map:_###_obj_###_:27
                this->codebox_01_lookup[21][1] = 9;//#map:_###_obj_###_:27
            }
            
            list codebox_01_result(number index) /*#map:_###_obj_###_:30*/
            {
                index = (index > 22 ? 22 : (index < 0 ? 0 : index));//#map:_###_obj_###_:32
            
                return {
                    this->codebox_01_lookup[(Index)index][0],
                    this->codebox_01_lookup[(Index)index][1]
                };//#map:_###_obj_###_:33
            }
            
            void counter_02_inc() {
                this->counter_02_count = ((bool)(this->counter_02_phase) ? this->counter_02_count + 1 : this->counter_02_count - 1);
            }
            
            void metro_01_onTransportChanged(number ) {}
            
            void metro_01_onBeatTimeChanged(number ) {}
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
                RNBO_UNUSED(inProcess);
                RNBO_UNUSED(engine);
                this->_currentTime = time;
                auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));
            
                if (offset >= (SampleIndex)(this->vs))
                    offset = (SampleIndex)(this->vs) - 1;
            
                if (offset < 0)
                    offset = 0;
            
                this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
            }
            
            void assign_defaults()
            {
                codebox_01_in1 = 0;
                counter_02_carryflag = 0;
                counter_02_direction = 2;
                counter_02_resetnext_number = 0;
                counter_02_resetnow_number = 0;
                counter_02_maximum = 22;
                counter_02_output = 0;
                counter_02_underflow_number = 0;
                counter_02_overflow_number = 0;
                counter_02_carry = 0;
                counter_02_minimum = 1;
                metro_01_on = 0;
                metro_01_interval = 10000;
                metro_01_interval_setter(metro_01_interval);
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.000022675736961451248;
                counter_02_count = 1;
                counter_02_phase = true;
                metro_01_last = -1;
                metro_01_next = -1;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number codebox_01_in1;
                list codebox_01_out1;
                Int counter_02_carryflag;
                number counter_02_direction;
                number counter_02_resetnext_number;
                number counter_02_resetnow_number;
                number counter_02_maximum;
                number counter_02_output;
                number counter_02_underflow_number;
                number counter_02_overflow_number;
                number counter_02_carry;
                number counter_02_minimum;
                number metro_01_on;
                number metro_01_interval;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                Index sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                RNBO::array<RNBO::array<Int, 2>, 22> codebox_01_lookup = { };
                list codebox_01_a;
                number counter_02_count;
                bool counter_02_phase;
                MillisecondTime metro_01_last;
                MillisecondTime metro_01_next;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                bool _isInitialized = false;
    };
    
    void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_28* operator->() {
        return this;
    }
    const RNBOSubpatcher_28* operator->() const {
        return this;
    }
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, 892732297, false);
        getEngine()->flushClockEvents(this, -1468824490, false);
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    number fromnormalized(Index index, number normalizedValue) {
        return this->convertFromNormalizedParameterValue(index, normalizedValue);
    }
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void param_01_value_set(number v) {
        v = this->param_01_value_constrain(v);
        this->param_01_value = v;
        this->sendParameter(0, false);
    
        if (this->param_01_value != this->param_01_lastValue) {
            this->getEngine()->presetTouched();
            this->param_01_lastValue = this->param_01_value;
        }
    
        this->p_01_in4_number_set(v);
    }
    
    void param_02_value_set(number v) {
        v = this->param_02_value_constrain(v);
        this->param_02_value = v;
        this->sendParameter(1, false);
    
        if (this->param_02_value != this->param_02_lastValue) {
            this->getEngine()->presetTouched();
            this->param_02_lastValue = this->param_02_value;
        }
    
        this->adsr_01_attack_set(v);
    }
    
    void param_03_value_set(number v) {
        v = this->param_03_value_constrain(v);
        this->param_03_value = v;
        this->sendParameter(2, false);
    
        if (this->param_03_value != this->param_03_lastValue) {
            this->getEngine()->presetTouched();
            this->param_03_lastValue = this->param_03_value;
        }
    
        this->adsr_01_decay_set(v);
    }
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(3, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->adsr_01_release_set(v);
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(4, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->adsr_01_sustain_set(v);
    }
    
    void loadmess_01_startupbang_bang() {
        this->loadmess_01_message_bang();
    }
    
    void param_06_value_set(number v) {
        v = this->param_06_value_constrain(v);
        this->param_06_value = v;
        this->sendParameter(5, false);
    
        if (this->param_06_value != this->param_06_lastValue) {
            this->getEngine()->presetTouched();
            this->param_06_lastValue = this->param_06_value;
        }
    
        this->p_03_in2_number_set(v);
    }
    
    void button_03_bangin_bang() {
        this->button_03_bangval_bang();
    }
    
    template<typename LISTTYPE> void message_01_listin_list_set(const LISTTYPE& v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_number_set(number v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_bang_bang() {
        this->message_01_trigger_bang();
    }
    
    void button_04_bangin_bang() {
        this->button_04_bangval_bang();
    }
    
    void adsr_01_mute_bang() {
        this->button_04_bangval_bang();
    }
    
    void deallocateSignals() {
        Index i;
    
        for (i = 0; i < 2; i++) {
            this->signals[i] = freeSignal(this->signals[i]);
        }
    
        this->ip_01_sigbuf = freeSignal(this->ip_01_sigbuf);
        this->adsr_01_triggerBuf = freeSignal(this->adsr_01_triggerBuf);
        this->adsr_01_triggerValueBuf = freeSignal(this->adsr_01_triggerValueBuf);
        this->zeroBuffer = freeSignal(this->zeroBuffer);
        this->dummyBuffer = freeSignal(this->dummyBuffer);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->mtof_01_innerScala_init();
        this->mtof_01_init();
        this->ip_01_init();
        this->scopetilde_01_init();
        this->message_01_init();
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->initializeObjects();
        }
    
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_02->setVoiceIndex(index);
        this->p_03->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_02->setNoteNumber(noteNumber);
        this->p_03->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void extractState(PatcherStateInterface& ) {}
    
    void applyState() {
        for (Index i = 0; i < 4; i++) {
    
            this->p_01[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
            this->p_01[(Index)i]->initialize();
            this->p_01[(Index)i]->setParameterOffset(this->getParameterOffset(this->p_01[0]));
            this->p_01[(Index)i]->setVoiceIndex(i + 1);
        }
    
    
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
    
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    }
    
    ParameterValue getPolyParameterValue(RNBOSubpatcher_28* voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        RNBOSubpatcher_28* voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 4; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface& subpatcher) const {
        if (addressOf(subpatcher) == addressOf(this->p_01[0]))
            return 6;
    
        if (addressOf(subpatcher) == addressOf(this->p_02))
            return 6 + this->p_01[0]->getNumParameters();
    
        if (addressOf(subpatcher) == addressOf(this->p_03))
            return 6 + this->p_01[0]->getNumParameters() + this->p_02->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (index) {
        case 892732297:
            {
            this->loadmess_01_startupbang_bang();
            break;
            }
        case -1468824490:
            {
            this->adsr_01_mute_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->startup();
        }
    
        this->p_02->startup();
        this->p_03->startup();
        this->getEngine()->scheduleClockEvent(this, 892732297, 0 + this->_currentTime);;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {
        for (Index i = 0; i < 4; i++) {
            this->p_01[i]->allocateDataRefs();
        }
    
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
        this->mtof_01_innerMtoF_buffer->requestSize(65536, 1);
        this->mtof_01_innerMtoF_buffer->setSampleRate(this->sr);
        this->mtof_01_innerMtoF_buffer = this->mtof_01_innerMtoF_buffer->allocateIfNeeded();
    }
    
    number param_01_value_constrain(number v) const {
        v = (v > 10 ? 10 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_01_in4_number_set(number v) {
        for (Index i = 0; i < 4; i++) {
            if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
                this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
            }
        }
    
        for (Index i = 0; i < 4; i++) {
            if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
                this->p_01[i]->eventinlet_03_out1_number_set(v);
            }
        }
    }
    
    number param_02_value_constrain(number v) const {
        v = (v > 100 ? 100 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_attack_set(number v) {
        this->adsr_01_attack = v;
    }
    
    number param_03_value_constrain(number v) const {
        v = (v > 100 ? 100 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_decay_set(number v) {
        this->adsr_01_decay = v;
    }
    
    number param_04_value_constrain(number v) const {
        v = (v > 3000 ? 3000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_release_set(number v) {
        this->adsr_01_release = v;
    }
    
    number param_05_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_sustain_set(number v) {
        this->adsr_01_sustain = v;
    }
    
    template<typename LISTTYPE> void p_03_in1_list_set(const LISTTYPE& v) {
        this->p_03->updateTime(this->_currentTime, (ENGINE*)nullptr);
        this->p_03->eventinlet_07_out1_list_set(v);
    }
    
    void loadmess_01_message_bang() {
        list v = this->loadmess_01_message;
        this->p_03_in1_list_set(v);
    }
    
    number param_06_value_constrain(number v) const {
        v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_03_in2_number_set(number v) {
        this->p_03->updateTime(this->_currentTime, (ENGINE*)nullptr);
        this->p_03->eventinlet_08_out1_number_set(v);
    }
    
    void p_03_in3_bang_bang() {
        this->p_03->updateTime(this->_currentTime, (ENGINE*)nullptr);
        this->p_03->eventinlet_09_out1_bang_bang();
    }
    
    void button_03_output_bang() {
        this->p_03_in3_bang_bang();
    }
    
    void button_03_bangval_bang() {
        ;
        this->button_03_output_bang();
    }
    
    template<typename LISTTYPE> void message_01_set_set(const LISTTYPE& v) {
        this->message_01_set = jsCreateListCopy(v);
    }
    
    template<typename LISTTYPE> void message_01_out_set(const LISTTYPE& ) {}
    
    void message_01_trigger_bang() {
        if ((bool)(this->message_01_set->length) || (bool)(false)) {
            this->message_01_out_set(this->message_01_set);
        }
    }
    
    void button_04_output_bang() {}
    
    void button_04_bangval_bang() {
        ;
        this->button_04_output_bang();
    }
    
    void notein_01_outchannel_set(number ) {}
    
    void notein_01_releasevelocity_set(number ) {}
    
    void trigger_03_out2_bang() {}
    
    void ip_01_value_set(number v) {
        this->ip_01_value = v;
        this->ip_01_fillSigBuf();
        this->ip_01_lastValue = v;
    }
    
    void expr_07_out1_set(number v) {
        this->expr_07_out1 = v;
        this->ip_01_value_set(this->expr_07_out1);
    }
    
    void expr_07_in1_set(number in1) {
        this->expr_07_in1 = in1;
    
        this->expr_07_out1_set(
            (this->expr_07_in2 == 0 ? 0 : (this->expr_07_in2 == 0. ? 0. : this->expr_07_in1 / this->expr_07_in2))
        );//#map:/_obj-13:1
    }
    
    void trigger_03_out1_set(number v) {
        this->expr_07_in1_set(v);
    }
    
    void trigger_03_input_number_set(number v) {
        this->trigger_03_out2_bang();
        this->trigger_03_out1_set(trunc(v));
    }
    
    void notein_01_velocity_set(number v) {
        this->trigger_03_input_number_set(v);
    }
    
    void p_02_in2_number_set(number v) {
        this->p_02->updateTime(this->_currentTime, (ENGINE*)nullptr);
        this->p_02->eventinlet_05_out1_number_set(v);
    }
    
    void expr_08_out1_set(number v) {
        this->expr_08_out1 = v;
        this->p_02_in2_number_set(this->expr_08_out1);
    }
    
    void expr_08_in1_set(number in1) {
        this->expr_08_in1 = in1;
    
        this->expr_08_out1_set(
            (this->expr_08_in2 == 0 ? 0 : (this->expr_08_in2 == 0. ? 0. : this->expr_08_in1 / this->expr_08_in2))
        );//#map:/_obj-62:1
    }
    
    void expr_08_in2_set(number v) {
        this->expr_08_in2 = v;
    }
    
    template<typename LISTTYPE> void pak_04_out_set(const LISTTYPE& v) {
        {
            if (v->length > 1)
                this->expr_08_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_08_in1_set(converted);
        }
    }
    
    void pak_04_in1_number_set(number v) {
        this->pak_04_data[0] = v;
        this->pak_04_out_set(this->pak_04_data);
    }
    
    void p_02_in1_number_set(number v) {
        this->p_02->updateTime(this->_currentTime, (ENGINE*)nullptr);
        this->p_02->eventinlet_04_out1_number_set(v);
    }
    
    void expr_05_out1_set(number v) {
        this->expr_05_out1 = v;
        this->p_02_in1_number_set(this->expr_05_out1);
    }
    
    void expr_05_in1_set(number in1) {
        this->expr_05_in1 = in1;
    
        this->expr_05_out1_set(
            (this->expr_05_in2 == 0 ? 0 : (this->expr_05_in2 == 0. ? 0. : this->expr_05_in1 / this->expr_05_in2))
        );//#map:/_obj-33:1
    }
    
    void expr_05_in2_set(number v) {
        this->expr_05_in2 = v;
    }
    
    template<typename LISTTYPE> void pak_03_out_set(const LISTTYPE& v) {
        {
            if (v->length > 1)
                this->expr_05_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_05_in1_set(converted);
        }
    }
    
    void pak_03_in1_number_set(number v) {
        this->pak_03_data[0] = v;
        this->pak_03_out_set(this->pak_03_data);
    }
    
    template<typename LISTTYPE> void mtof_01_out_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->pak_04_in1_number_set(converted);
        }
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->pak_03_in1_number_set(converted);
        }
    }
    
    template<typename LISTTYPE> void mtof_01_midivalue_set(const LISTTYPE& v) {
        this->mtof_01_midivalue = jsCreateListCopy(v);
        list tmp = list();
    
        for (Int i = 0; i < this->mtof_01_midivalue->length; i++) {
            tmp->push(
                this->mtof_01_innerMtoF_next(this->mtof_01_midivalue[(Index)i], this->mtof_01_base)
            );
        }
    
        this->mtof_01_out_set(tmp);
    }
    
    void trigger_02_out1_bang() {}
    
    void trigger_02_input_number_set(number v) {
        RNBO_UNUSED(v);
        this->trigger_02_out1_bang();
    }
    
    void notein_01_notenumber_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->mtof_01_midivalue_set(converted);
        }
    
        this->trigger_02_input_number_set(v);
    }
    
    void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (channel == this->notein_01_channel || this->notein_01_channel <= 0) {
            if (status == 144 || status == 128) {
                this->notein_01_outchannel_set(channel);
    
                if (status == 128) {
                    this->notein_01_releasevelocity_set(data[2]);
                    this->notein_01_velocity_set(0);
                } else {
                    this->notein_01_releasevelocity_set(0);
                    this->notein_01_velocity_set(data[2]);
                }
    
                this->notein_01_notenumber_set(data[1]);
            }
        }
    }
    
    void ctlin_01_outchannel_set(number ) {}
    
    void ctlin_01_outcontroller_set(number ) {}
    
    void fromnormalized_01_output_set(number v) {
        this->param_01_value_set(v);
    }
    
    void fromnormalized_01_input_set(number v) {
        this->fromnormalized_01_output_set(this->fromnormalized(0, v));
    }
    
    void expr_06_out1_set(number v) {
        this->expr_06_out1 = v;
        this->fromnormalized_01_input_set(this->expr_06_out1);
    }
    
    void expr_06_in1_set(number in1) {
        this->expr_06_in1 = in1;
        this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:expr_06:1
    }
    
    void ctlin_01_value_set(number v) {
        this->expr_06_in1_set(v);
    }
    
    void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
            this->ctlin_01_outchannel_set(channel);
            this->ctlin_01_outcontroller_set(data[1]);
            this->ctlin_01_value_set(data[2]);
            this->ctlin_01_status = 0;
        }
    }
    
    void ctlin_02_outchannel_set(number ) {}
    
    void ctlin_02_outcontroller_set(number ) {}
    
    void fromnormalized_02_output_set(number v) {
        this->param_02_value_set(v);
    }
    
    void fromnormalized_02_input_set(number v) {
        this->fromnormalized_02_output_set(this->fromnormalized(1, v));
    }
    
    void expr_09_out1_set(number v) {
        this->expr_09_out1 = v;
        this->fromnormalized_02_input_set(this->expr_09_out1);
    }
    
    void expr_09_in1_set(number in1) {
        this->expr_09_in1 = in1;
        this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:expr_09:1
    }
    
    void ctlin_02_value_set(number v) {
        this->expr_09_in1_set(v);
    }
    
    void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
            this->ctlin_02_outchannel_set(channel);
            this->ctlin_02_outcontroller_set(data[1]);
            this->ctlin_02_value_set(data[2]);
            this->ctlin_02_status = 0;
        }
    }
    
    void ctlin_03_outchannel_set(number ) {}
    
    void ctlin_03_outcontroller_set(number ) {}
    
    void fromnormalized_03_output_set(number v) {
        this->param_03_value_set(v);
    }
    
    void fromnormalized_03_input_set(number v) {
        this->fromnormalized_03_output_set(this->fromnormalized(2, v));
    }
    
    void expr_10_out1_set(number v) {
        this->expr_10_out1 = v;
        this->fromnormalized_03_input_set(this->expr_10_out1);
    }
    
    void expr_10_in1_set(number in1) {
        this->expr_10_in1 = in1;
        this->expr_10_out1_set(this->expr_10_in1 * this->expr_10_in2);//#map:expr_10:1
    }
    
    void ctlin_03_value_set(number v) {
        this->expr_10_in1_set(v);
    }
    
    void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
            this->ctlin_03_outchannel_set(channel);
            this->ctlin_03_outcontroller_set(data[1]);
            this->ctlin_03_value_set(data[2]);
            this->ctlin_03_status = 0;
        }
    }
    
    void ctlin_04_outchannel_set(number ) {}
    
    void ctlin_04_outcontroller_set(number ) {}
    
    void fromnormalized_04_output_set(number v) {
        this->param_04_value_set(v);
    }
    
    void fromnormalized_04_input_set(number v) {
        this->fromnormalized_04_output_set(this->fromnormalized(3, v));
    }
    
    void expr_11_out1_set(number v) {
        this->expr_11_out1 = v;
        this->fromnormalized_04_input_set(this->expr_11_out1);
    }
    
    void expr_11_in1_set(number in1) {
        this->expr_11_in1 = in1;
        this->expr_11_out1_set(this->expr_11_in1 * this->expr_11_in2);//#map:expr_11:1
    }
    
    void ctlin_04_value_set(number v) {
        this->expr_11_in1_set(v);
    }
    
    void ctlin_04_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 0xB0 && (channel == this->ctlin_04_channel || this->ctlin_04_channel == -1) && (data[1] == this->ctlin_04_controller || this->ctlin_04_controller == -1)) {
            this->ctlin_04_outchannel_set(channel);
            this->ctlin_04_outcontroller_set(data[1]);
            this->ctlin_04_value_set(data[2]);
            this->ctlin_04_status = 0;
        }
    }
    
    void ctlin_05_outchannel_set(number ) {}
    
    void ctlin_05_outcontroller_set(number ) {}
    
    void fromnormalized_05_output_set(number v) {
        this->param_05_value_set(v);
    }
    
    void fromnormalized_05_input_set(number v) {
        this->fromnormalized_05_output_set(this->fromnormalized(4, v));
    }
    
    void expr_12_out1_set(number v) {
        this->expr_12_out1 = v;
        this->fromnormalized_05_input_set(this->expr_12_out1);
    }
    
    void expr_12_in1_set(number in1) {
        this->expr_12_in1 = in1;
        this->expr_12_out1_set(this->expr_12_in1 * this->expr_12_in2);//#map:expr_12:1
    }
    
    void ctlin_05_value_set(number v) {
        this->expr_12_in1_set(v);
    }
    
    void ctlin_05_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 0xB0 && (channel == this->ctlin_05_channel || this->ctlin_05_channel == -1) && (data[1] == this->ctlin_05_controller || this->ctlin_05_controller == -1)) {
            this->ctlin_05_outchannel_set(channel);
            this->ctlin_05_outcontroller_set(data[1]);
            this->ctlin_05_value_set(data[2]);
            this->ctlin_05_status = 0;
        }
    }
    
    void ctlin_06_outchannel_set(number ) {}
    
    void ctlin_06_outcontroller_set(number ) {}
    
    void fromnormalized_06_output_set(number v) {
        this->param_06_value_set(v);
    }
    
    void fromnormalized_06_input_set(number v) {
        this->fromnormalized_06_output_set(this->fromnormalized(5, v));
    }
    
    void expr_13_out1_set(number v) {
        this->expr_13_out1 = v;
        this->fromnormalized_06_input_set(this->expr_13_out1);
    }
    
    void expr_13_in1_set(number in1) {
        this->expr_13_in1 = in1;
        this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:expr_13:1
    }
    
    void ctlin_06_value_set(number v) {
        this->expr_13_in1_set(v);
    }
    
    void ctlin_06_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (status == 0xB0 && (channel == this->ctlin_06_channel || this->ctlin_06_channel == -1) && (data[1] == this->ctlin_06_controller || this->ctlin_06_controller == -1)) {
            this->ctlin_06_outchannel_set(channel);
            this->ctlin_06_outcontroller_set(data[1]);
            this->ctlin_06_value_set(data[2]);
            this->ctlin_06_status = 0;
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void p_02_out3_number_set(number ) {}
    
    void p_01_in2_number_set(number v) {
        for (Index i = 0; i < 4; i++) {
            if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
                this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
            }
        }
    
        for (Index i = 0; i < 4; i++) {
            if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
                this->p_01[i]->eventinlet_02_out1_number_set(v);
            }
        }
    }
    
    void unpack_02_out2_set(number v) {
        this->unpack_02_out2 = v;
        this->p_01_in2_number_set(v);
    }
    
    void p_01_target_set(number v) {
        this->p_01_target = v;
    }
    
    void unpack_02_out1_set(number v) {
        this->unpack_02_out1 = v;
        this->p_01_target_set(v);
    }
    
    template<typename LISTTYPE> void unpack_02_input_list_set(const LISTTYPE& v) {
        if (v->length > 1)
            this->unpack_02_out2_set(v[1]);
    
        if (v->length > 0)
            this->unpack_02_out1_set(v[0]);
    }
    
    template<typename LISTTYPE> void p_02_out2_list_set(const LISTTYPE& v) {
        this->unpack_02_input_list_set(v);
    }
    
    void p_01_in1_number_set(number v) {
        for (Index i = 0; i < 4; i++) {
            if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
                this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
            }
        }
    
        for (Index i = 0; i < 4; i++) {
            if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
                this->p_01[i]->eventinlet_01_out1_number_set(v);
            }
        }
    }
    
    void unpack_01_out2_set(number v) {
        this->unpack_01_out2 = v;
        this->p_01_in1_number_set(v);
    }
    
    void unpack_01_out1_set(number v) {
        this->unpack_01_out1 = v;
        this->p_01_target_set(v);
    }
    
    template<typename LISTTYPE> void unpack_01_input_list_set(const LISTTYPE& v) {
        if (v->length > 1)
            this->unpack_01_out2_set(v[1]);
    
        if (v->length > 0)
            this->unpack_01_out1_set(v[0]);
    }
    
    template<typename LISTTYPE> void p_02_out1_list_set(const LISTTYPE& v) {
        this->unpack_01_input_list_set(v);
    }
    
    void pak_04_in2_number_set(number v) {
        this->pak_04_data[1] = v;
        this->pak_04_out_set(this->pak_04_data);
    }
    
    void unpack_03_out2_set(number v) {
        this->unpack_03_out2 = v;
        this->pak_04_in2_number_set(v);
    }
    
    void pak_03_in2_number_set(number v) {
        this->pak_03_data[1] = v;
        this->pak_03_out_set(this->pak_03_data);
    }
    
    void unpack_03_out1_set(number v) {
        this->unpack_03_out1 = v;
        this->pak_03_in2_number_set(v);
    }
    
    template<typename LISTTYPE> void unpack_03_input_list_set(const LISTTYPE& v) {
        if (v->length > 1)
            this->unpack_03_out2_set(v[1]);
    
        if (v->length > 0)
            this->unpack_03_out1_set(v[0]);
    }
    
    template<typename LISTTYPE> void trigger_04_out2_set(const LISTTYPE& v) {
        this->unpack_03_input_list_set(v);
    }
    
    void p_02_in3_bang_bang() {
        this->p_02->updateTime(this->_currentTime, (ENGINE*)nullptr);
        this->p_02->eventinlet_06_out1_bang_bang();
    }
    
    void trigger_04_out1_bang() {
        this->p_02_in3_bang_bang();
    }
    
    template<typename LISTTYPE> void trigger_04_input_list_set(const LISTTYPE& v) {
        this->trigger_04_out2_set(v);
        this->trigger_04_out1_bang();
    }
    
    template<typename LISTTYPE> void p_03_out1_list_set(const LISTTYPE& v) {
        this->message_01_set_set(v);
        this->trigger_04_input_list_set(v);
    }
    
    void p_02_perform(Index n) {
        // subpatcher: freq_calc
        this->p_02->process(nullptr, 0, nullptr, 0, n);
    }
    
    void ip_01_perform(SampleValue * out, Index n) {
        auto __ip_01_lastValue = this->ip_01_lastValue;
        auto __ip_01_lastIndex = this->ip_01_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_01_lastIndex ? __ip_01_lastValue : this->ip_01_sigbuf[(Index)i]);
        }
    
        __ip_01_lastIndex = 0;
        this->ip_01_lastIndex = __ip_01_lastIndex;
    }
    
    void adsr_01_perform(
        number attack,
        number decay,
        number sustain,
        number release,
        const SampleValue * trigger_signal,
        SampleValue * out,
        Index n
    ) {
        auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
        auto __adsr_01_time = this->adsr_01_time;
        auto __adsr_01_amplitude = this->adsr_01_amplitude;
        auto __adsr_01_outval = this->adsr_01_outval;
        auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
        auto __adsr_01_phase = this->adsr_01_phase;
        auto __adsr_01_legato = this->adsr_01_legato;
        auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
        auto __adsr_01_maxsustain = this->adsr_01_maxsustain;
        auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
        bool bangMute = false;
    
        for (Index i = 0; i < n; i++) {
            number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
            number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
            number clampedsustain = (__adsr_01_maxsustain > __adsr_01_mspersamp ? __adsr_01_maxsustain : __adsr_01_mspersamp);
            number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
            number currentTriggerVal = trigger_signal[(Index)i];
    
            if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
                if ((bool)(__adsr_01_legato)) {
                    if (__adsr_01_phase != 0) {
                        __adsr_01_startingpoint = __adsr_01_outval;
                    } else {
                        __adsr_01_startingpoint = 0;
                    }
                } else {
                    __adsr_01_startingpoint = 0;
                }
    
                __adsr_01_amplitude = currentTriggerVal;
                __adsr_01_phase = 3;
                __adsr_01_time = 0.0;
                bangMute = false;
            } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                    __adsr_01_time = 0.0;
                }
            }
    
            __adsr_01_time += __adsr_01_mspersamp;
    
            if (__adsr_01_phase == 0) {
                __adsr_01_outval = 0;
            } else if (__adsr_01_phase == 3) {
                if (__adsr_01_time > clampedattack) {
                    __adsr_01_time -= clampedattack;
                    __adsr_01_phase = 2;
                    __adsr_01_outval = __adsr_01_amplitude;
                } else {
                    __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
                }
            } else if (__adsr_01_phase == 2) {
                if (__adsr_01_time > clampeddecay) {
                    __adsr_01_time -= clampeddecay;
                    __adsr_01_phase = 1;
                    __adsr_01_outval = __adsr_01_amplitude * sustain;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
                }
            } else if (__adsr_01_phase == 1) {
                if (__adsr_01_time > clampedsustain && __adsr_01_maxsustain > -1) {
                    __adsr_01_time -= clampedsustain;
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * sustain;
                }
            } else if (__adsr_01_phase == 4) {
                if (__adsr_01_time > clampedrelease) {
                    __adsr_01_time = 0;
                    __adsr_01_phase = 0;
                    __adsr_01_outval = 0;
                    __adsr_01_amplitude = 0;
                    bangMute = true;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
                }
            }
    
            out[(Index)i] = __adsr_01_outval;
            this->adsr_01_triggerBuf[(Index)i] = 0;
            this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
            __adsr_01_lastTriggerVal = currentTriggerVal;
        }
    
        if ((bool)(bangMute)) {
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1468824490,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                0
            );;
        }
    
        this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
        this->adsr_01_phase = __adsr_01_phase;
        this->adsr_01_startingpoint = __adsr_01_startingpoint;
        this->adsr_01_outval = __adsr_01_outval;
        this->adsr_01_amplitude = __adsr_01_amplitude;
        this->adsr_01_time = __adsr_01_time;
    }
    
    void scopetilde_01_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_01_ysign = this->scopetilde_01_ysign;
        auto __scopetilde_01_ymonitorvalue = this->scopetilde_01_ymonitorvalue;
        auto __scopetilde_01_xsign = this->scopetilde_01_xsign;
        auto __scopetilde_01_xmonitorvalue = this->scopetilde_01_xmonitorvalue;
        auto __scopetilde_01_mode = this->scopetilde_01_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_01_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_01_xmonitorvalue) {
                    __scopetilde_01_xmonitorvalue = xabsval;
                    __scopetilde_01_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_01_ymonitorvalue) {
                    __scopetilde_01_ymonitorvalue = yabsval;
                    __scopetilde_01_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_01_xmonitorvalue = xval;
                __scopetilde_01_xsign = 1;
                __scopetilde_01_ymonitorvalue = yval;
                __scopetilde_01_ysign = 1;
            }
    
            this->scopetilde_01_effectiveCount--;
    
            if (this->scopetilde_01_effectiveCount <= 0) {
                this->scopetilde_01_updateEffectiveCount();
                this->scopetilde_01_monitorbuffer->push(__scopetilde_01_xmonitorvalue * __scopetilde_01_xsign);
    
                if (__scopetilde_01_mode == 1)
                    __scopetilde_01_xmonitorvalue = 0;
    
                if (this->scopetilde_01_monitorbuffer->length >= 128 * (1 + 0)) {
                    ;
                    this->scopetilde_01_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_01_xmonitorvalue = __scopetilde_01_xmonitorvalue;
        this->scopetilde_01_xsign = __scopetilde_01_xsign;
        this->scopetilde_01_ymonitorvalue = __scopetilde_01_ymonitorvalue;
        this->scopetilde_01_ysign = __scopetilde_01_ysign;
    }
    
    void p_01_perform(const SampleValue * in3, SampleValue * out1, Index n) {
        // subpatcher: test
        ConstSampleArray<1> ins = {in3};
    
        SampleArray<1> outs = {out1};
    
        for (number chan = 0; chan < 1; chan++)
            zeroSignal(outs[(Index)chan], n);
    
        for (Index i = 0; i < 4; i++)
            this->p_01[(Index)i]->process(ins, 1, outs, 1, n);
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void p_03_perform(Index n) {
        // subpatcher: ratio_sequencer
        this->p_03->process(nullptr, 0, nullptr, 0, n);
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number mtof_01_innerMtoF_next(number midivalue, number tuning) {
        if (midivalue == this->mtof_01_innerMtoF_lastInValue && tuning == this->mtof_01_innerMtoF_lastTuning)
            return this->mtof_01_innerMtoF_lastOutValue;
    
        this->mtof_01_innerMtoF_lastInValue = midivalue;
        this->mtof_01_innerMtoF_lastTuning = tuning;
        number result = 0;
    
        {
            result = rnbo_exp(.057762265 * (midivalue - 69.0));
        }
    
        this->mtof_01_innerMtoF_lastOutValue = tuning * result;
        return this->mtof_01_innerMtoF_lastOutValue;
    }
    
    void mtof_01_innerMtoF_reset() {
        this->mtof_01_innerMtoF_lastInValue = 0;
        this->mtof_01_innerMtoF_lastOutValue = 0;
        this->mtof_01_innerMtoF_lastTuning = 0;
    }
    
    void mtof_01_innerScala_mid(Int v) {
        this->mtof_01_innerScala_kbmMid = v;
        this->mtof_01_innerScala_updateRefFreq();
    }
    
    void mtof_01_innerScala_ref(Int v) {
        this->mtof_01_innerScala_kbmRefNum = v;
        this->mtof_01_innerScala_updateRefFreq();
    }
    
    void mtof_01_innerScala_base(number v) {
        this->mtof_01_innerScala_kbmRefFreq = v;
        this->mtof_01_innerScala_updateRefFreq();
    }
    
    void mtof_01_innerScala_init() {
        list sclValid = {
            12,
            100,
            0,
            200,
            0,
            300,
            0,
            400,
            0,
            500,
            0,
            600,
            0,
            700,
            0,
            800,
            0,
            900,
            0,
            1000,
            0,
            1100,
            0,
            2,
            1
        };
    
        this->mtof_01_innerScala_updateScale(sclValid);
    }
    
    template<typename LISTTYPE = list> void mtof_01_innerScala_update(const LISTTYPE& scale, const LISTTYPE& map) {
        if (scale->length > 0) {
            this->mtof_01_innerScala_updateScale(scale);
        }
    
        if (map->length > 0) {
            this->mtof_01_innerScala_updateMap(map);
        }
    }
    
    number mtof_01_innerScala_mtof(number note) {
        if ((bool)(this->mtof_01_innerScala_lastValid) && this->mtof_01_innerScala_lastNote == note) {
            return this->mtof_01_innerScala_lastFreq;
        }
    
        array<Int, 2> degoct = this->mtof_01_innerScala_applyKBM(note);
        number out = 0;
    
        if (degoct[1] > 0) {
            out = this->mtof_01_innerScala_applySCL(degoct[0], fract(note), this->mtof_01_innerScala_refFreq);
        }
    
        this->mtof_01_innerScala_updateLast(note, out);
        return out;
    }
    
    number mtof_01_innerScala_ftom(number hz) {
        if (hz <= 0.0) {
            return 0.0;
        }
    
        if ((bool)(this->mtof_01_innerScala_lastValid) && this->mtof_01_innerScala_lastFreq == hz) {
            return this->mtof_01_innerScala_lastNote;
        }
    
        array<number, 2> df = this->mtof_01_innerScala_hztodeg(hz);
        Int degree = (Int)(df[0]);
        number frac = df[1];
        number out = 0;
    
        if (this->mtof_01_innerScala_kbmSize == 0) {
            out = this->mtof_01_innerScala_kbmMid + degree;
        } else {
            array<Int, 2> octdeg = this->mtof_01_innerScala_octdegree(degree, this->mtof_01_innerScala_kbmOctaveDegree);
            number oct = (number)(octdeg[0]);
            Int index = (Int)(octdeg[1]);
            Index entry = 0;
    
            for (Index i = 0; i < this->mtof_01_innerScala_kbmMapSize; i++) {
                if (index == this->mtof_01_innerScala_kbmValid[(Index)(i + this->mtof_01_innerScala_KBM_MAP_OFFSET)]) {
                    entry = i;
                    break;
                }
            }
    
            out = oct * this->mtof_01_innerScala_kbmSize + entry + this->mtof_01_innerScala_kbmMid;
        }
    
        out = out + frac;
        this->mtof_01_innerScala_updateLast(out, hz);
        return this->mtof_01_innerScala_lastNote;
    }
    
    template<typename LISTTYPE = list> Int mtof_01_innerScala_updateScale(const LISTTYPE& scl) {
        if (scl->length < 1) {
            return 0;
        }
    
        number sclDataEntries = scl[0] * 2 + 1;
    
        if (sclDataEntries <= scl->length) {
            this->mtof_01_innerScala_lastValid = false;
            this->mtof_01_innerScala_sclExpMul = {};
            number last = 1;
    
            for (Index i = 1; i < sclDataEntries; i += 2) {
                const number c = (const number)(scl[(Index)(i + 0)]);
                const number d = (const number)(scl[(Index)(i + 1)]);
    
                if (d <= 0) {
                    last = c / (number)1200;
                } else {
                    last = rnbo_log2(c / d);
                }
    
                this->mtof_01_innerScala_sclExpMul->push(last);
            }
    
            this->mtof_01_innerScala_sclOctaveMul = last;
            this->mtof_01_innerScala_sclEntryCount = (Int)(this->mtof_01_innerScala_sclExpMul->length);
    
            if (scl->length >= sclDataEntries + 3) {
                this->mtof_01_innerScala_kbmMid = (Int)(scl[(Index)(sclDataEntries + 2)]);
                this->mtof_01_innerScala_kbmRefNum = (Int)(scl[(Index)(sclDataEntries + 1)]);
                this->mtof_01_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
                this->mtof_01_innerScala_kbmSize = (Int)(0);
            }
    
            this->mtof_01_innerScala_updateRefFreq();
            return 1;
        }
    
        return 0;
    }
    
    template<typename LISTTYPE = list> Int mtof_01_innerScala_updateMap(const LISTTYPE& kbm) {
        list _kbm = kbm;
    
        if (_kbm->length == 1 && _kbm[0] == 0.0) {
            _kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
        }
    
        if (_kbm->length >= 6 && _kbm[0] >= 0.0) {
            this->mtof_01_innerScala_lastValid = false;
            Index size = (Index)(_kbm[0]);
            Int octave = 12;
    
            if (_kbm->length > 6) {
                octave = (Int)(_kbm[6]);
            }
    
            if (size > 0 && _kbm->length < this->mtof_01_innerScala_KBM_MAP_OFFSET) {
                return 0;
            }
    
            this->mtof_01_innerScala_kbmSize = (Int)(size);
            this->mtof_01_innerScala_kbmMin = (Int)(_kbm[1]);
            this->mtof_01_innerScala_kbmMax = (Int)(_kbm[2]);
            this->mtof_01_innerScala_kbmMid = (Int)(_kbm[3]);
            this->mtof_01_innerScala_kbmRefNum = (Int)(_kbm[4]);
            this->mtof_01_innerScala_kbmRefFreq = _kbm[5];
            this->mtof_01_innerScala_kbmOctaveDegree = octave;
            this->mtof_01_innerScala_kbmValid = _kbm;
            this->mtof_01_innerScala_kbmMapSize = (_kbm->length - this->mtof_01_innerScala_KBM_MAP_OFFSET > _kbm->length ? _kbm->length : (_kbm->length - this->mtof_01_innerScala_KBM_MAP_OFFSET < 0 ? 0 : _kbm->length - this->mtof_01_innerScala_KBM_MAP_OFFSET));
            this->mtof_01_innerScala_updateRefFreq();
            return 1;
        }
    
        return 0;
    }
    
    void mtof_01_innerScala_updateLast(number note, number freq) {
        this->mtof_01_innerScala_lastValid = true;
        this->mtof_01_innerScala_lastNote = note;
        this->mtof_01_innerScala_lastFreq = freq;
    }
    
    array<number, 2> mtof_01_innerScala_hztodeg(number hz) {
        number hza = rnbo_abs(hz);
    
        number octave = rnbo_floor(
            rnbo_log2(hza / this->mtof_01_innerScala_refFreq) / this->mtof_01_innerScala_sclOctaveMul
        );
    
        Int i = 0;
        number frac = 0;
        number n = 0;
    
        for (; i < this->mtof_01_innerScala_sclEntryCount; i++) {
            number c = this->mtof_01_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_01_innerScala_refFreq);
            n = this->mtof_01_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_01_innerScala_refFreq);
    
            if (c <= hza && hza < n) {
                if (c != hza) {
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
    
                break;
            }
        }
    
        if (i == this->mtof_01_innerScala_sclEntryCount && n != hza) {
            number c = n;
            n = this->mtof_01_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_01_innerScala_refFreq);
            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
        }
    
        number deg = i + octave * this->mtof_01_innerScala_sclEntryCount;
    
        {
            deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
            frac = 0.0;
        }
    
        return {deg, frac};
    }
    
    array<Int, 2> mtof_01_innerScala_octdegree(Int degree, Int count) {
        Int octave = 0;
        Int index = 0;
    
        if (degree < 0) {
            octave = -(1 + (-1 - degree) / count);
            index = -degree % count;
    
            if (index > 0) {
                index = count - index;
            }
        } else {
            octave = degree / count;
            index = degree % count;
        }
    
        return {octave, index};
    }
    
    array<Int, 2> mtof_01_innerScala_applyKBM(number note) {
        if ((this->mtof_01_innerScala_kbmMin == this->mtof_01_innerScala_kbmMax && this->mtof_01_innerScala_kbmMax == 0) || (note >= this->mtof_01_innerScala_kbmMin && note <= this->mtof_01_innerScala_kbmMax)) {
            Int degree = (Int)(rnbo_floor(note - this->mtof_01_innerScala_kbmMid));
    
            if (this->mtof_01_innerScala_kbmSize == 0) {
                return {degree, 1};
            }
    
            array<Int, 2> octdeg = this->mtof_01_innerScala_octdegree(degree, this->mtof_01_innerScala_kbmSize);
            Int octave = (Int)(octdeg[0]);
            Index index = (Index)(octdeg[1]);
    
            if (this->mtof_01_innerScala_kbmMapSize > index) {
                degree = (Int)(this->mtof_01_innerScala_kbmValid[(Index)(this->mtof_01_innerScala_KBM_MAP_OFFSET + index)]);
    
                if (degree >= 0) {
                    return {degree + octave * this->mtof_01_innerScala_kbmOctaveDegree, 1};
                }
            }
        }
    
        return {-1, 0};
    }
    
    number mtof_01_innerScala_applySCL(Int degree, number frac, number refFreq) {
        array<Int, 2> octdeg = this->mtof_01_innerScala_octdegree(degree, this->mtof_01_innerScala_sclEntryCount);
        return this->mtof_01_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
    }
    
    number mtof_01_innerScala_applySCLOctIndex(number octave, Int index, number frac, number refFreq) {
        number p = 0;
    
        if (index > 0) {
            p = this->mtof_01_innerScala_sclExpMul[(Index)(index - 1)];
        }
    
        if (frac > 0) {
            p = this->linearinterp(frac, p, this->mtof_01_innerScala_sclExpMul[(Index)index]);
        } else if (frac < 0) {
            p = this->linearinterp(-frac, this->mtof_01_innerScala_sclExpMul[(Index)index], p);
        }
    
        return refFreq * rnbo_pow(2, p + octave * this->mtof_01_innerScala_sclOctaveMul);
    }
    
    void mtof_01_innerScala_updateRefFreq() {
        this->mtof_01_innerScala_lastValid = false;
        Int refOffset = (Int)(this->mtof_01_innerScala_kbmRefNum - this->mtof_01_innerScala_kbmMid);
    
        if (refOffset == 0) {
            this->mtof_01_innerScala_refFreq = this->mtof_01_innerScala_kbmRefFreq;
        } else {
            Int base = (Int)(this->mtof_01_innerScala_kbmSize);
    
            if (base < 1) {
                base = this->mtof_01_innerScala_sclEntryCount;
            }
    
            array<Int, 2> octdeg = this->mtof_01_innerScala_octdegree(refOffset, base);
            number oct = (number)(octdeg[0]);
            Int index = (Int)(octdeg[1]);
    
            if (base > 0) {
                oct = oct + rnbo_floor(index / base);
                index = index % base;
            }
    
            if (index >= 0 && index < this->mtof_01_innerScala_kbmSize) {
                if (index < (Int)(this->mtof_01_innerScala_kbmMapSize)) {
                    index = (Int)(this->mtof_01_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_01_innerScala_KBM_MAP_OFFSET)]);
                } else {
                    index = -1;
                }
            }
    
            if (index < 0 || index > (Int)(this->mtof_01_innerScala_sclExpMul->length))
                {} else {
                number p = 0;
    
                if (index > 0) {
                    p = this->mtof_01_innerScala_sclExpMul[(Index)(index - 1)];
                }
    
                this->mtof_01_innerScala_refFreq = this->mtof_01_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_01_innerScala_sclOctaveMul);
            }
        }
    }
    
    void mtof_01_innerScala_reset() {
        this->mtof_01_innerScala_lastValid = false;
        this->mtof_01_innerScala_lastNote = 0;
        this->mtof_01_innerScala_lastFreq = 0;
        this->mtof_01_innerScala_sclEntryCount = 0;
        this->mtof_01_innerScala_sclOctaveMul = 1;
        this->mtof_01_innerScala_sclExpMul = {};
        this->mtof_01_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
        this->mtof_01_innerScala_kbmMid = 60;
        this->mtof_01_innerScala_kbmRefNum = 69;
        this->mtof_01_innerScala_kbmRefFreq = 440;
        this->mtof_01_innerScala_kbmSize = 0;
        this->mtof_01_innerScala_kbmMin = 0;
        this->mtof_01_innerScala_kbmMax = 0;
        this->mtof_01_innerScala_kbmOctaveDegree = 12;
        this->mtof_01_innerScala_kbmMapSize = 0;
        this->mtof_01_innerScala_refFreq = 261.63;
    }
    
    void mtof_01_init() {
        this->mtof_01_innerScala_update(this->mtof_01_scale, this->mtof_01_map);
    }
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
    }
    
    void ip_01_init() {
        this->ip_01_lastValue = this->ip_01_value;
    }
    
    void ip_01_fillSigBuf() {
        if ((bool)(this->ip_01_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_01_lastIndex); i < k; i++) {
                if (this->ip_01_resetCount > 0) {
                    this->ip_01_sigbuf[(Index)i] = 1;
                    this->ip_01_resetCount--;
                } else {
                    this->ip_01_sigbuf[(Index)i] = this->ip_01_lastValue;
                }
            }
    
            this->ip_01_lastIndex = k;
        }
    }
    
    void ip_01_dspsetup(bool force) {
        if ((bool)(this->ip_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_01_lastIndex = 0;
        this->ip_01_setupDone = true;
    }
    
    void scopetilde_01_init() {
        this->scopetilde_01_monitorbuffer->reserve(128 * (1 + 0));
    }
    
    void scopetilde_01_updateEffectiveCount() {
        number effectiveCount = 42 * 1 + 42 * 0;
        this->scopetilde_01_effectiveCount = this->maximum(effectiveCount, 42);
    }
    
    void scopetilde_01_dspsetup(bool force) {
        if ((bool)(this->scopetilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_01_mode = 1;
        }
    
        ;
        this->scopetilde_01_updateEffectiveCount();
        this->scopetilde_01_setupDone = true;
    }
    
    void adsr_01_dspsetup(bool force) {
        if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->adsr_01_mspersamp = (number)1000 / this->sr;
        this->adsr_01_setupDone = true;
    }
    
    void param_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_02_value;
    }
    
    void param_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_02_value_set(preset["value"]);
    }
    
    void param_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_03_value;
    }
    
    void param_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_03_value_set(preset["value"]);
    }
    
    void param_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_04_value;
    }
    
    void param_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_04_value_set(preset["value"]);
    }
    
    void param_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_05_value;
    }
    
    void param_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_05_value_set(preset["value"]);
    }
    
    void param_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_06_value;
    }
    
    void param_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_06_value_set(preset["value"]);
    }
    
    void message_01_init() {
        this->message_01_set_set(listbase<number, 2>{2, 5});
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
        RNBO_UNUSED(inProcess);
        RNBO_UNUSED(engine);
        this->_currentTime = time;
        auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));
    
        if (offset >= (SampleIndex)(this->vs))
            offset = (SampleIndex)(this->vs) - 1;
    
        if (offset < 0)
            offset = 0;
    
        this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
    }
    
    void assign_defaults()
    {
        unpack_01_out1 = 0;
        unpack_01_out2 = 0;
        p_01_target = 0;
        unpack_02_out1 = 0;
        unpack_02_out2 = 0;
        p_02_target = 0;
        expr_05_in1 = 0;
        expr_05_in2 = 1;
        expr_05_out1 = 0;
        mtof_01_base = 440;
        notein_01_channel = 0;
        unpack_03_out1 = 0;
        unpack_03_out2 = 0;
        param_01_value = 0;
        ip_01_value = 0;
        ip_01_impulse = 0;
        expr_07_in1 = 0;
        expr_07_in2 = 127;
        expr_07_out1 = 0;
        expr_08_in1 = 0;
        expr_08_in2 = 1;
        expr_08_out1 = 0;
        adsr_01_trigger_number = 0;
        adsr_01_attack = 10;
        adsr_01_decay = 100;
        adsr_01_sustain = 0.8;
        adsr_01_release = 1000;
        adsr_01_legato = false;
        adsr_01_maxsustain = -1;
        param_02_value = 0;
        param_03_value = 0;
        param_04_value = 0;
        param_05_value = 0;
        loadmess_01_message = { 1 };
        p_03_target = 0;
        param_06_value = 0;
        ctlin_01_input = 0;
        ctlin_01_controller = 0;
        ctlin_01_channel = -1;
        expr_06_in1 = 0;
        expr_06_in2 = 0.007874015748;
        expr_06_out1 = 0;
        ctlin_02_input = 0;
        ctlin_02_controller = 0;
        ctlin_02_channel = -1;
        expr_09_in1 = 0;
        expr_09_in2 = 0.007874015748;
        expr_09_out1 = 0;
        ctlin_03_input = 0;
        ctlin_03_controller = 0;
        ctlin_03_channel = -1;
        expr_10_in1 = 0;
        expr_10_in2 = 0.007874015748;
        expr_10_out1 = 0;
        ctlin_04_input = 0;
        ctlin_04_controller = 0;
        ctlin_04_channel = -1;
        expr_11_in1 = 0;
        expr_11_in2 = 0.007874015748;
        expr_11_out1 = 0;
        ctlin_05_input = 0;
        ctlin_05_controller = 0;
        ctlin_05_channel = -1;
        expr_12_in1 = 0;
        expr_12_in2 = 0.007874015748;
        expr_12_out1 = 0;
        ctlin_06_input = 0;
        ctlin_06_controller = 0;
        ctlin_06_channel = -1;
        expr_13_in1 = 0;
        expr_13_in2 = 0.007874015748;
        expr_13_out1 = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.000022675736961451248;
        pak_03_data = { 0, 0 };
        mtof_01_innerMtoF_lastInValue = 0;
        mtof_01_innerMtoF_lastOutValue = 0;
        mtof_01_innerMtoF_lastTuning = 0;
        mtof_01_innerScala_lastValid = false;
        mtof_01_innerScala_lastNote = 0;
        mtof_01_innerScala_lastFreq = 0;
        mtof_01_innerScala_sclEntryCount = 0;
        mtof_01_innerScala_sclOctaveMul = 1;
        mtof_01_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
        mtof_01_innerScala_kbmMid = 60;
        mtof_01_innerScala_kbmRefNum = 69;
        mtof_01_innerScala_kbmRefFreq = 440;
        mtof_01_innerScala_kbmSize = 0;
        mtof_01_innerScala_kbmMin = 0;
        mtof_01_innerScala_kbmMax = 0;
        mtof_01_innerScala_kbmOctaveDegree = 12;
        mtof_01_innerScala_kbmMapSize = 0;
        mtof_01_innerScala_refFreq = 261.63;
        notein_01_status = 0;
        notein_01_byte1 = -1;
        notein_01_inchan = 0;
        param_01_lastValue = 0;
        ip_01_lastIndex = 0;
        ip_01_lastValue = 0;
        ip_01_resetCount = 0;
        ip_01_sigbuf = nullptr;
        ip_01_setupDone = false;
        pak_04_data = { 0, 0 };
        scopetilde_01_lastValue = 0;
        scopetilde_01_effectiveCount = 256;
        scopetilde_01_xsign = 1;
        scopetilde_01_ysign = 1;
        scopetilde_01_mode = 0;
        scopetilde_01_setupDone = false;
        adsr_01_phase = 1;
        adsr_01_mspersamp = 0;
        adsr_01_time = 0;
        adsr_01_lastTriggerVal = 0;
        adsr_01_amplitude = 0;
        adsr_01_outval = 0;
        adsr_01_startingpoint = 0;
        adsr_01_triggerBuf = nullptr;
        adsr_01_triggerValueBuf = nullptr;
        adsr_01_setupDone = false;
        param_02_lastValue = 0;
        param_03_lastValue = 0;
        param_04_lastValue = 0;
        param_05_lastValue = 0;
        param_06_lastValue = 0;
        ctlin_01_status = 0;
        ctlin_01_byte1 = -1;
        ctlin_01_inchan = 0;
        ctlin_02_status = 0;
        ctlin_02_byte1 = -1;
        ctlin_02_inchan = 0;
        ctlin_03_status = 0;
        ctlin_03_byte1 = -1;
        ctlin_03_inchan = 0;
        ctlin_04_status = 0;
        ctlin_04_byte1 = -1;
        ctlin_04_inchan = 0;
        ctlin_05_status = 0;
        ctlin_05_byte1 = -1;
        ctlin_05_inchan = 0;
        ctlin_06_status = 0;
        ctlin_06_byte1 = -1;
        ctlin_06_inchan = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number unpack_01_out1;
        number unpack_01_out2;
        number p_01_target;
        number unpack_02_out1;
        number unpack_02_out2;
        number p_02_target;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_out1;
        list mtof_01_midivalue;
        list mtof_01_scale;
        list mtof_01_map;
        number mtof_01_base;
        number notein_01_channel;
        number unpack_03_out1;
        number unpack_03_out2;
        number param_01_value;
        number ip_01_value;
        number ip_01_impulse;
        number expr_07_in1;
        number expr_07_in2;
        number expr_07_out1;
        number expr_08_in1;
        number expr_08_in2;
        number expr_08_out1;
        number adsr_01_trigger_number;
        number adsr_01_attack;
        number adsr_01_decay;
        number adsr_01_sustain;
        number adsr_01_release;
        number adsr_01_legato;
        number adsr_01_maxsustain;
        number param_02_value;
        number param_03_value;
        number param_04_value;
        number param_05_value;
        list loadmess_01_message;
        number p_03_target;
        number param_06_value;
        list message_01_set;
        number ctlin_01_input;
        number ctlin_01_controller;
        number ctlin_01_channel;
        number expr_06_in1;
        number expr_06_in2;
        number expr_06_out1;
        number ctlin_02_input;
        number ctlin_02_controller;
        number ctlin_02_channel;
        number expr_09_in1;
        number expr_09_in2;
        number expr_09_out1;
        number ctlin_03_input;
        number ctlin_03_controller;
        number ctlin_03_channel;
        number expr_10_in1;
        number expr_10_in2;
        number expr_10_out1;
        number ctlin_04_input;
        number ctlin_04_controller;
        number ctlin_04_channel;
        number expr_11_in1;
        number expr_11_in2;
        number expr_11_out1;
        number ctlin_05_input;
        number ctlin_05_controller;
        number ctlin_05_channel;
        number expr_12_in1;
        number expr_12_in2;
        number expr_12_out1;
        number ctlin_06_input;
        number ctlin_06_controller;
        number ctlin_06_channel;
        number expr_13_in1;
        number expr_13_in2;
        number expr_13_out1;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        Index sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[2];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        list pak_03_data;
        number mtof_01_innerMtoF_lastInValue;
        number mtof_01_innerMtoF_lastOutValue;
        number mtof_01_innerMtoF_lastTuning;
        SampleBufferRef mtof_01_innerMtoF_buffer;
        const Index mtof_01_innerScala_KBM_MAP_OFFSET = 7;
        bool mtof_01_innerScala_lastValid;
        number mtof_01_innerScala_lastNote;
        number mtof_01_innerScala_lastFreq;
        Int mtof_01_innerScala_sclEntryCount;
        number mtof_01_innerScala_sclOctaveMul;
        list mtof_01_innerScala_sclExpMul;
        list mtof_01_innerScala_kbmValid;
        Int mtof_01_innerScala_kbmMid;
        Int mtof_01_innerScala_kbmRefNum;
        number mtof_01_innerScala_kbmRefFreq;
        Int mtof_01_innerScala_kbmSize;
        Int mtof_01_innerScala_kbmMin;
        Int mtof_01_innerScala_kbmMax;
        Int mtof_01_innerScala_kbmOctaveDegree;
        Index mtof_01_innerScala_kbmMapSize;
        number mtof_01_innerScala_refFreq;
        Int notein_01_status;
        Int notein_01_byte1;
        Int notein_01_inchan;
        number param_01_lastValue;
        SampleIndex ip_01_lastIndex;
        number ip_01_lastValue;
        SampleIndex ip_01_resetCount;
        signal ip_01_sigbuf;
        bool ip_01_setupDone;
        list pak_04_data;
        number scopetilde_01_lastValue;
        number scopetilde_01_effectiveCount;
        number scopetilde_01_xmonitorvalue;
        number scopetilde_01_ymonitorvalue;
        list scopetilde_01_monitorbuffer;
        number scopetilde_01_xsign;
        number scopetilde_01_ysign;
        Int scopetilde_01_mode;
        bool scopetilde_01_setupDone;
        Int adsr_01_phase;
        number adsr_01_mspersamp;
        number adsr_01_time;
        number adsr_01_lastTriggerVal;
        number adsr_01_amplitude;
        number adsr_01_outval;
        number adsr_01_startingpoint;
        signal adsr_01_triggerBuf;
        signal adsr_01_triggerValueBuf;
        bool adsr_01_setupDone;
        number param_02_lastValue;
        number param_03_lastValue;
        number param_04_lastValue;
        number param_05_lastValue;
        number param_06_lastValue;
        Int ctlin_01_status;
        Int ctlin_01_byte1;
        Int ctlin_01_inchan;
        Int ctlin_02_status;
        Int ctlin_02_byte1;
        Int ctlin_02_inchan;
        Int ctlin_03_status;
        Int ctlin_03_byte1;
        Int ctlin_03_inchan;
        Int ctlin_04_status;
        Int ctlin_04_byte1;
        Int ctlin_04_inchan;
        Int ctlin_05_status;
        Int ctlin_05_byte1;
        Int ctlin_05_inchan;
        Int ctlin_06_status;
        Int ctlin_06_byte1;
        Int ctlin_06_inchan;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_25 p_01[4];
        RNBOSubpatcher_26 p_02;
        RNBOSubpatcher_27 p_03;
        bool _isInitialized = false;
};

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(inProcess ? time + sampsToMs(this->vs) : time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

number fromnormalized(Index index, number normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(0, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->poly_MOD_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(1, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->poly_ATT_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(2, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->poly_DEC_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(3, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->poly_REL_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(4, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->poly_SUS_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(5, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->poly_METRO_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void deallocateSignals() {
    Index i;
    this->globaltransport_tempo = freeSignal(this->globaltransport_tempo);
    this->globaltransport_state = freeSignal(this->globaltransport_state);
    this->zeroBuffer = freeSignal(this->zeroBuffer);
    this->dummyBuffer = freeSignal(this->dummyBuffer);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

void setProbingTarget(MessageTag ) {}

void fillRNBODefaultSinus(DataRef& ref) {
    SampleBuffer buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    SampleBuffer buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    case 1:
        {
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
        }
    }
}

void allocateDataRefs() {
    for (Index i = 0; i < 4; i++) {
        this->poly[i]->allocateDataRefs();
    }

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 4; i++) {
        this->poly[i]->initializeObjects();
    }
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void extractState(PatcherStateInterface& ) {}

void applyState() {
    for (Index i = 0; i < 4; i++) {

        this->poly[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->poly[(Index)i]->initialize();
        this->poly[(Index)i]->setParameterOffset(this->getParameterOffset(this->poly[0]));
        this->poly[(Index)i]->setVoiceIndex(i + 1);
    }
}

ParameterIndex getParameterOffset(BaseInterface& subpatcher) const {
    if (addressOf(subpatcher) == addressOf(this->poly[0]))
        return 6;

    return 0;
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);

    for (Index i = 0; i < 4; i++) {
        this->poly[i]->startup();
    }

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    this->processParamInitEvents();
}

number param_07_value_constrain(number v) const {
    v = (v > 10 ? 10 : (v < 0 ? 0 : v));
    return v;
}

void poly_MOD_set(number v) {
    for (number i = 0; i < 4; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(0, v, this->_currentTime);
        }
    }
}

number param_08_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void poly_ATT_set(number v) {
    for (number i = 0; i < 4; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(1, v, this->_currentTime);
        }
    }
}

number param_09_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void poly_DEC_set(number v) {
    for (number i = 0; i < 4; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(2, v, this->_currentTime);
        }
    }
}

number param_10_value_constrain(number v) const {
    v = (v > 3000 ? 3000 : (v < 0 ? 0 : v));
    return v;
}

void poly_REL_set(number v) {
    for (number i = 0; i < 4; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(3, v, this->_currentTime);
        }
    }
}

number param_11_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void poly_SUS_set(number v) {
    for (number i = 0; i < 4; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(4, v, this->_currentTime);
        }
    }
}

number param_12_value_constrain(number v) const {
    v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
    return v;
}

void poly_METRO_set(number v) {
    for (number i = 0; i < 4; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(5, v, this->_currentTime);
        }
    }
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void poly_target_set(number v) {
    this->poly_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->poly_target_set(v);
}

void poly_midiininternal_set(number v) {
    Index sendlen = 0;
    this->poly_currentStatus = parseMidi(this->poly_currentStatus, (Int)(v), this->poly_mididata[0]);

    switch ((int)this->poly_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->poly_mididata[0] = (uint8_t)(v);
        this->poly_mididata[1] = 0;
        break;
        }
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        {
        this->poly_mididata[1] = (uint8_t)(v);

        if (this->poly_currentStatus == MIDI_ProgramChange || this->poly_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        {
        this->poly_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
        }
    }

    if (sendlen > 0) {
        number i;

        if (this->poly_target > 0 && this->poly_target <= 4) {
            i = this->poly_target - 1;
            this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
        } else if (this->poly_target == 0) {
            for (i = 0; i < 4; i++) {
                this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->poly_midiininternal_set(v);
}

void poly_noteNumber_set(number v) {
    if (this->poly_target > 0) {
        this->poly[(Index)(this->poly_target - 1)]->setNoteNumber((Int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->poly_noteNumber_set(v);
}

template<typename LISTTYPE> void midinotecontroller_01_voicestatus_set(const LISTTYPE& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

template<typename LISTTYPE> void poly_voicestatus_set(const LISTTYPE& v) {
    this->midinotecontroller_01_voicestatus_set(v);
}

void poly_activevoices_set(number ) {}

template<typename LISTTYPE> void poly_mute_set(const LISTTYPE& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 4; i++) {
            this->poly[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 4) {
            this->poly[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->poly_voicestatus_set(tmp);
    this->poly_activevoices_set(this->poly_calcActiveVoices());
}

template<typename LISTTYPE> void midinotecontroller_01_mute_set(const LISTTYPE& v) {
    this->poly_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    Int val = (Int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (Int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
        }
    case MIDI_SecondByteReceived:
        {
        this->midinotecontroller_01_byte1 = val;
        break;
        }
    case MIDI_NoteOn:
        {
        {
            bool sendnoteoff = true;
            Int target = 1;
            MillisecondTime oldest = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[0]);
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Int i = 0; i < 4; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        MillisecondTime candidate_ontime = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[(Index)i]);

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff(target);

            Int i = (Int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->_currentTime;
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend(i);
            this->midinotecontroller_01_sendpressure(i);
            this->midinotecontroller_01_sendtimbre(i);
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((BinOpInt)MIDI_NoteOnMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_NoteOff:
        {
        {
            Int target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Int i = 0; i < 4; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                Int i = (Int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
        }
    case MIDI_Aftertouch:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_CC:
        {
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 4; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
                }
            case MIDI_CC_TimbreMSB:
                {
                {
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Int k = (Int)(v);
                    number timbre = (BinOpInt)(((BinOpInt)((BinOpInt)k & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32));
                    this->midinotecontroller_01_channel_timbre[(Index)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F)] = timbre;

                    for (Int i = 0; i < 4; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
                }
            case MIDI_CC_TimbreLSB:
                {
                {
                    break;
                }
                }
            case MIDI_CC_AllNotesOff:
                {
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
        }
    case MIDI_ProgramChange:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_ChannelPressure:
        {
        {
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Int i = 0; i < 4; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    Int k = (Int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
        }
    case MIDI_PitchBend:
        {
        {
            number bendamount = (BinOpInt)((BinOpInt)this->midinotecontroller_01_byte1 | (BinOpInt)((BinOpInt)val << imod_nocast((UBinOpInt)7, 32)));
            Int channel = (Int)((BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Int i = 0; i < 4; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
        }
    }
}

void poly_midiin_set(number v) {
    this->poly_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_midiout_set(number v) {
    this->poly_midiin_set(v);
}

void midiin_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_midiout_set(data[i]);
    }
}

void ctlin_07_outchannel_set(number ) {}

void ctlin_07_outcontroller_set(number ) {}

void fromnormalized_07_output_set(number v) {
    this->param_07_value_set(v);
}

void fromnormalized_07_input_set(number v) {
    this->fromnormalized_07_output_set(this->fromnormalized(0, v));
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->fromnormalized_07_input_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;
    this->expr_14_out1_set(this->expr_14_in1 * this->expr_14_in2);//#map:expr_14:1
}

void ctlin_07_value_set(number v) {
    this->expr_14_in1_set(v);
}

void ctlin_07_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_07_channel || this->ctlin_07_channel == -1) && (data[1] == this->ctlin_07_controller || this->ctlin_07_controller == -1)) {
        this->ctlin_07_outchannel_set(channel);
        this->ctlin_07_outcontroller_set(data[1]);
        this->ctlin_07_value_set(data[2]);
        this->ctlin_07_status = 0;
    }
}

void ctlin_08_outchannel_set(number ) {}

void ctlin_08_outcontroller_set(number ) {}

void fromnormalized_08_output_set(number v) {
    this->param_08_value_set(v);
}

void fromnormalized_08_input_set(number v) {
    this->fromnormalized_08_output_set(this->fromnormalized(1, v));
}

void expr_15_out1_set(number v) {
    this->expr_15_out1 = v;
    this->fromnormalized_08_input_set(this->expr_15_out1);
}

void expr_15_in1_set(number in1) {
    this->expr_15_in1 = in1;
    this->expr_15_out1_set(this->expr_15_in1 * this->expr_15_in2);//#map:expr_15:1
}

void ctlin_08_value_set(number v) {
    this->expr_15_in1_set(v);
}

void ctlin_08_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_08_channel || this->ctlin_08_channel == -1) && (data[1] == this->ctlin_08_controller || this->ctlin_08_controller == -1)) {
        this->ctlin_08_outchannel_set(channel);
        this->ctlin_08_outcontroller_set(data[1]);
        this->ctlin_08_value_set(data[2]);
        this->ctlin_08_status = 0;
    }
}

void ctlin_09_outchannel_set(number ) {}

void ctlin_09_outcontroller_set(number ) {}

void fromnormalized_09_output_set(number v) {
    this->param_09_value_set(v);
}

void fromnormalized_09_input_set(number v) {
    this->fromnormalized_09_output_set(this->fromnormalized(2, v));
}

void expr_16_out1_set(number v) {
    this->expr_16_out1 = v;
    this->fromnormalized_09_input_set(this->expr_16_out1);
}

void expr_16_in1_set(number in1) {
    this->expr_16_in1 = in1;
    this->expr_16_out1_set(this->expr_16_in1 * this->expr_16_in2);//#map:expr_16:1
}

void ctlin_09_value_set(number v) {
    this->expr_16_in1_set(v);
}

void ctlin_09_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_09_channel || this->ctlin_09_channel == -1) && (data[1] == this->ctlin_09_controller || this->ctlin_09_controller == -1)) {
        this->ctlin_09_outchannel_set(channel);
        this->ctlin_09_outcontroller_set(data[1]);
        this->ctlin_09_value_set(data[2]);
        this->ctlin_09_status = 0;
    }
}

void ctlin_10_outchannel_set(number ) {}

void ctlin_10_outcontroller_set(number ) {}

void fromnormalized_10_output_set(number v) {
    this->param_10_value_set(v);
}

void fromnormalized_10_input_set(number v) {
    this->fromnormalized_10_output_set(this->fromnormalized(3, v));
}

void expr_17_out1_set(number v) {
    this->expr_17_out1 = v;
    this->fromnormalized_10_input_set(this->expr_17_out1);
}

void expr_17_in1_set(number in1) {
    this->expr_17_in1 = in1;
    this->expr_17_out1_set(this->expr_17_in1 * this->expr_17_in2);//#map:expr_17:1
}

void ctlin_10_value_set(number v) {
    this->expr_17_in1_set(v);
}

void ctlin_10_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_10_channel || this->ctlin_10_channel == -1) && (data[1] == this->ctlin_10_controller || this->ctlin_10_controller == -1)) {
        this->ctlin_10_outchannel_set(channel);
        this->ctlin_10_outcontroller_set(data[1]);
        this->ctlin_10_value_set(data[2]);
        this->ctlin_10_status = 0;
    }
}

void ctlin_11_outchannel_set(number ) {}

void ctlin_11_outcontroller_set(number ) {}

void fromnormalized_11_output_set(number v) {
    this->param_11_value_set(v);
}

void fromnormalized_11_input_set(number v) {
    this->fromnormalized_11_output_set(this->fromnormalized(4, v));
}

void expr_18_out1_set(number v) {
    this->expr_18_out1 = v;
    this->fromnormalized_11_input_set(this->expr_18_out1);
}

void expr_18_in1_set(number in1) {
    this->expr_18_in1 = in1;
    this->expr_18_out1_set(this->expr_18_in1 * this->expr_18_in2);//#map:expr_18:1
}

void ctlin_11_value_set(number v) {
    this->expr_18_in1_set(v);
}

void ctlin_11_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_11_channel || this->ctlin_11_channel == -1) && (data[1] == this->ctlin_11_controller || this->ctlin_11_controller == -1)) {
        this->ctlin_11_outchannel_set(channel);
        this->ctlin_11_outcontroller_set(data[1]);
        this->ctlin_11_value_set(data[2]);
        this->ctlin_11_status = 0;
    }
}

void ctlin_12_outchannel_set(number ) {}

void ctlin_12_outcontroller_set(number ) {}

void fromnormalized_12_output_set(number v) {
    this->param_12_value_set(v);
}

void fromnormalized_12_input_set(number v) {
    this->fromnormalized_12_output_set(this->fromnormalized(5, v));
}

void expr_19_out1_set(number v) {
    this->expr_19_out1 = v;
    this->fromnormalized_12_input_set(this->expr_19_out1);
}

void expr_19_in1_set(number in1) {
    this->expr_19_in1 = in1;
    this->expr_19_out1_set(this->expr_19_in1 * this->expr_19_in2);//#map:expr_19:1
}

void ctlin_12_value_set(number v) {
    this->expr_19_in1_set(v);
}

void ctlin_12_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_12_channel || this->ctlin_12_channel == -1) && (data[1] == this->ctlin_12_controller || this->ctlin_12_controller == -1)) {
        this->ctlin_12_outchannel_set(channel);
        this->ctlin_12_outcontroller_set(data[1]);
        this->ctlin_12_value_set(data[2]);
        this->ctlin_12_status = 0;
    }
}

void poly_perform(SampleValue * out1, SampleValue * out2, Index n) {
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 4; i++)
        this->poly[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

number poly_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 4; i++) {
            if ((bool)(!(bool)(this->poly[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 4; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(Int target) {
    Int i = (Int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(Int v) {
    if (v >= 0 && v < 4) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        Int totalbendamount = (Int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_PitchBendMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)totalbendamount & (BinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)((BinOpInt)totalbendamount >> imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)7, 32), 32)) & (BinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(Int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_ChannelPressureMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(Int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> imod_nocast((UBinOpInt)7, 32)) & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Int i = 1; i <= 4; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

number globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    number diffInBeats = diff * this->globaltransport_getTempo(time) * 0.008 / (number)480;
    return beatTimeBase + diffInBeats;
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample((SampleIndex)(offset)) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        SampleIndex offset = (SampleIndex)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_state, this->vs, state, (Index)(offset));
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;

        if (rnbo_abs(beattime - this->globaltransport_getBeatTime(time)) > 0.001) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = (MillisecondTime)(this->sampstoms(sampleOffset));
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

void globaltransport_setBBUBase(
    MillisecondTime time,
    number numerator,
    number denominator,
    number bars,
    number beats,
    number units
) {
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    bars--;
    beats--;
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;

    while (units > beatLengthInUnits) {
        units -= beatLengthInUnits;
        beats++;
    }

    number targetBeatTime = bars * numerator + beats + units / beatLengthInUnits;
    this->globaltransport_bbuBase = targetBeatTime - beatsIncCurrenttDenom;
}

array<number, 3> globaltransport_getBBU(MillisecondTime time) {
    array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);
    number numerator = currentSig[0];
    number denominator = currentSig[1];
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;
    number targetBeatTime = beatsIncCurrenttDenom + this->globaltransport_bbuBase;
    number currentBars = 0;
    number currentBeats = 0;
    number currentUnits = 0;

    if (targetBeatTime >= 0) {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;
        currentBeats = trunc(targetBeatTime);
        targetBeatTime -= currentBeats;
        currentUnits = targetBeatTime * beatLengthInUnits;
    } else {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;

        if (targetBeatTime != 0) {
            currentBars -= 1;
            currentBeats = trunc(targetBeatTime);
            targetBeatTime -= currentBeats;
            currentBeats = numerator + currentBeats;
            currentUnits = targetBeatTime * beatLengthInUnits;

            if (currentUnits != 0) {
                currentUnits = beatLengthInUnits + currentUnits;
                currentBeats -= 1;
            }
        }
    }

    return {currentBars + 1, currentBeats + 1, currentUnits};
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (Int)(numerator), (Int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            array<number, 3> bbu = this->globaltransport_getBBU(time);
            this->globaltransport_setBBUBase(time, numerator, denominator, bbu[0], bbu[1], bbu[2]);
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

array<number, 3> globaltransport_getBBUAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBBU(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setBBU(MillisecondTime time, number bars, number beats, number units, bool notify) {
    RNBO_UNUSED(notify);
    array<number, 2> sig = this->globaltransport_getTimeSignature(time);
    number numerator = sig[0];
    number denominator = sig[1];
    this->globaltransport_setBBUBase(time, numerator, denominator, bars, beats, units);
    return true;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (Int)(this->globaltransport_timeSignatureChanges[0]),
                (Int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
    RNBO_UNUSED(inProcess);
    RNBO_UNUSED(engine);
    this->_currentTime = time;
    auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));

    if (offset >= (SampleIndex)(this->vs))
        offset = (SampleIndex)(this->vs) - 1;

    if (offset < 0)
        offset = 0;

    this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
}

void assign_defaults()
{
    midiin_port = 0;
    midiout_port = 0;
    param_07_value = 0;
    param_08_value = 0;
    param_09_value = 0;
    param_10_value = 0;
    param_11_value = 0;
    param_12_value = 0;
    poly_target = 0;
    poly_midiin = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    ctlin_07_input = 0;
    ctlin_07_controller = 0;
    ctlin_07_channel = -1;
    expr_14_in1 = 0;
    expr_14_in2 = 0.007874015748;
    expr_14_out1 = 0;
    ctlin_08_input = 0;
    ctlin_08_controller = 0;
    ctlin_08_channel = -1;
    expr_15_in1 = 0;
    expr_15_in2 = 0.007874015748;
    expr_15_out1 = 0;
    ctlin_09_input = 0;
    ctlin_09_controller = 0;
    ctlin_09_channel = -1;
    expr_16_in1 = 0;
    expr_16_in2 = 0.007874015748;
    expr_16_out1 = 0;
    ctlin_10_input = 0;
    ctlin_10_controller = 0;
    ctlin_10_channel = -1;
    expr_17_in1 = 0;
    expr_17_in2 = 0.007874015748;
    expr_17_out1 = 0;
    ctlin_11_input = 0;
    ctlin_11_controller = 0;
    ctlin_11_channel = -1;
    expr_18_in1 = 0;
    expr_18_in2 = 0.007874015748;
    expr_18_out1 = 0;
    ctlin_12_input = 0;
    ctlin_12_controller = 0;
    ctlin_12_channel = -1;
    expr_19_in1 = 0;
    expr_19_in2 = 0.007874015748;
    expr_19_out1 = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    midiout_currentStatus = -1;
    midiout_status = -1;
    midiout_byte1 = -1;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    poly_currentStatus = -1;
    poly_mididata[0] = 0;
    poly_mididata[1] = 0;
    poly_mididata[2] = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    ctlin_07_status = 0;
    ctlin_07_byte1 = -1;
    ctlin_07_inchan = 0;
    ctlin_08_status = 0;
    ctlin_08_byte1 = -1;
    ctlin_08_inchan = 0;
    ctlin_09_status = 0;
    ctlin_09_byte1 = -1;
    ctlin_09_inchan = 0;
    ctlin_10_status = 0;
    ctlin_10_byte1 = -1;
    ctlin_10_inchan = 0;
    ctlin_11_status = 0;
    ctlin_11_byte1 = -1;
    ctlin_11_inchan = 0;
    ctlin_12_status = 0;
    ctlin_12_byte1 = -1;
    ctlin_12_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_bbuBase = 0;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
    	static constexpr auto& name0 = "RNBODefaultSinus";
    	static constexpr auto& file0 = "";
    	static constexpr auto& tag0 = "buffer~";
    	static constexpr auto& name1 = "RNBODefaultMtofLookupTable256";
    	static constexpr auto& file1 = "";
    	static constexpr auto& tag1 = "buffer~";
    	DataRefStrings* operator->() { return this; }
    	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number midiin_port;
    number midiout_port;
    number param_07_value;
    number param_08_value;
    number param_09_value;
    number param_10_value;
    number param_11_value;
    number param_12_value;
    number poly_target;
    number poly_midiin;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    number ctlin_07_input;
    number ctlin_07_controller;
    number ctlin_07_channel;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    number ctlin_08_input;
    number ctlin_08_controller;
    number ctlin_08_channel;
    number expr_15_in1;
    number expr_15_in2;
    number expr_15_out1;
    number ctlin_09_input;
    number ctlin_09_controller;
    number ctlin_09_channel;
    number expr_16_in1;
    number expr_16_in2;
    number expr_16_out1;
    number ctlin_10_input;
    number ctlin_10_controller;
    number ctlin_10_channel;
    number expr_17_in1;
    number expr_17_in2;
    number expr_17_out1;
    number ctlin_11_input;
    number ctlin_11_controller;
    number ctlin_11_channel;
    number expr_18_in1;
    number expr_18_in2;
    number expr_18_out1;
    number ctlin_12_input;
    number ctlin_12_controller;
    number ctlin_12_channel;
    number expr_19_in1;
    number expr_19_in2;
    number expr_19_out1;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    Int midiout_currentStatus;
    Int midiout_status;
    Int midiout_byte1;
    list midiout_sysex;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    Int poly_currentStatus;
    uint8_t poly_mididata[3];
    Int midinotecontroller_01_currentStatus;
    Int midinotecontroller_01_status;
    Int midinotecontroller_01_byte1;
    Int midinotecontroller_01_zone_masterchannel;
    Int midinotecontroller_01_zone_numnotechannels;
    Int midinotecontroller_01_zone_masterpitchbendrange;
    Int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    MillisecondTime midinotecontroller_01_voice_lastontime[4] = { };
    number midinotecontroller_01_voice_notenumber[4] = { };
    number midinotecontroller_01_voice_channel[4] = { };
    number midinotecontroller_01_voice_state[4] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    Int ctlin_07_status;
    Int ctlin_07_byte1;
    Int ctlin_07_inchan;
    Int ctlin_08_status;
    Int ctlin_08_byte1;
    Int ctlin_08_inchan;
    Int ctlin_09_status;
    Int ctlin_09_byte1;
    Int ctlin_09_inchan;
    Int ctlin_10_status;
    Int ctlin_10_byte1;
    Int ctlin_10_inchan;
    Int ctlin_11_status;
    Int ctlin_11_byte1;
    Int ctlin_11_inchan;
    Int ctlin_12_status;
    Int ctlin_12_byte1;
    Int ctlin_12_inchan;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    number globaltransport_bbuBase;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef RNBODefaultSinus;
    DataRef RNBODefaultMtofLookupTable256;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_28 poly[4];
    bool _isInitialized = false;
};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

