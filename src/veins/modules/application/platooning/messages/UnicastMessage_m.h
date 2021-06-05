//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/platooning/messages/UnicastMessage.msg.
//

#ifndef __UNICASTMESSAGE_M_H
#define __UNICASTMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>veins/modules/application/platooning/messages/UnicastMessage.msg:18</tt> by nedtool.
 * <pre>
 * enum UnicastMessageType
 * {
 *     DATA = 0;
 *     ACK = 1;
 * }
 * </pre>
 */
enum UnicastMessageType {
    DATA = 0,
    ACK = 1
};

/**
 * Class generated from <tt>veins/modules/application/platooning/messages/UnicastMessage.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // Unicast message sent by the unicast protocol
 * //
 * packet UnicastMessage
 * {
 *     //destination MAC address
 *     int destination;
 *     //source MAC address
 *     int source;
 *     //sequence number
 *     int sequenceNumber;
 *     //message type, data or ack
 *     int type \@enum(UnicastMessageType);
 *     //priority for the message (will be then mapped onto an AC)
 *     //0 = AC_BK
 *     //1 = AC_BE
 *     //2 = AC_VI
 *     //3 = AC_VO
 *     int priority = 0;
 *     //receive power in dBm
 *     double recvPower_dBm;
 *     //channel number
 *     int channel;
 * }
 * </pre>
 */
class UnicastMessage : public ::omnetpp::cPacket
{
  protected:
    int destination;
    int source;
    int sequenceNumber;
    int type;
    int priority;
    double recvPower_dBm;
    int channel;

  private:
    void copy(const UnicastMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const UnicastMessage&);

  public:
    UnicastMessage(const char *name=nullptr, short kind=0);
    UnicastMessage(const UnicastMessage& other);
    virtual ~UnicastMessage();
    UnicastMessage& operator=(const UnicastMessage& other);
    virtual UnicastMessage *dup() const override {return new UnicastMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getDestination() const;
    virtual void setDestination(int destination);
    virtual int getSource() const;
    virtual void setSource(int source);
    virtual int getSequenceNumber() const;
    virtual void setSequenceNumber(int sequenceNumber);
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual double getRecvPower_dBm() const;
    virtual void setRecvPower_dBm(double recvPower_dBm);
    virtual int getChannel() const;
    virtual void setChannel(int channel);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const UnicastMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, UnicastMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __UNICASTMESSAGE_M_H

