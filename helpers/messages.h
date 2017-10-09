#ifndef _KS_MESSAGES_H_
#define _KS_MESSAGES_H_

#include <string>
#include <vector>
#include <map>
#include <array>


namespace ks
{

#ifndef _KS_OBJECT_
#define _KS_OBJECT_

class KSObject
{
public:
	static inline const std::string nameStatic() { return ""; }
    virtual inline const std::string name() const = 0;
	virtual std::string serialize() const = 0;
	virtual unsigned int deserialize(const std::string &, unsigned int = 0) = 0;
};

#endif // _KS_OBJECT_


namespace messages
{

class Message : public KSObject
{

protected:

	std::string __type;
	std::string __payload;

	bool __has_type;
	bool __has_payload;


public: // getters

	inline std::string type() const
	{
		return __type;
	}
	
	inline std::string payload() const
	{
		return __payload;
	}
	

public: // reference getters

	inline std::string &ref_type() const
	{
		return (std::string&) __type;
	}
	
	inline std::string &ref_payload() const
	{
		return (std::string&) __payload;
	}
	

public: // setters

	inline void type(const std::string &type)
	{
		__type = type;
		has_type(true);
	}
	
	inline void payload(const std::string &payload)
	{
		__payload = payload;
		has_payload(true);
	}
	

public: // has_attribute getters

	inline bool has_type() const
	{
		return __has_type;
	}
	
	inline bool has_payload() const
	{
		return __has_payload;
	}
	

public: // has_attribute setters

	inline void has_type(const bool &has_type)
	{
		__has_type = has_type;
	}
	
	inline void has_payload(const bool &has_payload)
	{
		__has_payload = has_payload;
	}
	

public:

	Message()
	{
		has_type(false);
		has_payload(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Message";
	}
	
	virtual inline const std::string name() const
	{
		return "Message";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize type
		s += __has_type;
		if (__has_type)
		{
			std::string tmp0 = "";
			unsigned int tmp2 = __type.size();
			auto tmp3 = reinterpret_cast<char*>(&tmp2);
			tmp0 += std::string(tmp3, sizeof(unsigned int));
			while (tmp0.size() && tmp0.back() == 0)
				tmp0.pop_back();
			unsigned char tmp5 = tmp0.size();
			auto tmp6 = reinterpret_cast<char*>(&tmp5);
			s += std::string(tmp6, sizeof(unsigned char));
			s += tmp0;
			
			s += __type;
		}
		
		// serialize payload
		s += __has_payload;
		if (__has_payload)
		{
			std::string tmp7 = "";
			unsigned int tmp9 = __payload.size();
			auto tmp10 = reinterpret_cast<char*>(&tmp9);
			tmp7 += std::string(tmp10, sizeof(unsigned int));
			while (tmp7.size() && tmp7.back() == 0)
				tmp7.pop_back();
			unsigned char tmp12 = tmp7.size();
			auto tmp13 = reinterpret_cast<char*>(&tmp12);
			s += std::string(tmp13, sizeof(unsigned char));
			s += tmp7;
			
			s += __payload;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize type
		__has_type = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_type)
		{
			unsigned char tmp14;
			tmp14 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp15 = std::string(&s[offset], tmp14);
			offset += tmp14;
			while (tmp15.size() < sizeof(unsigned int))
				tmp15 += '\x00';
			unsigned int tmp16;
			tmp16 = *((unsigned int*) (&tmp15[0]));
			
			__type = s.substr(offset, tmp16);
			offset += tmp16;
		}
		
		// deserialize payload
		__has_payload = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_payload)
		{
			unsigned char tmp17;
			tmp17 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp18 = std::string(&s[offset], tmp17);
			offset += tmp17;
			while (tmp18.size() < sizeof(unsigned int))
				tmp18 += '\x00';
			unsigned int tmp19;
			tmp19 = *((unsigned int*) (&tmp18[0]));
			
			__payload = s.substr(offset, tmp19);
			offset += tmp19;
		}
		
		return offset;
	}
};


class JoinOfflineGame : public KSObject
{

protected:

	std::string __team_nickname;
	std::string __agent_name;

	bool __has_team_nickname;
	bool __has_agent_name;


public: // getters

	inline std::string team_nickname() const
	{
		return __team_nickname;
	}
	
	inline std::string agent_name() const
	{
		return __agent_name;
	}
	

public: // reference getters

	inline std::string &ref_team_nickname() const
	{
		return (std::string&) __team_nickname;
	}
	
	inline std::string &ref_agent_name() const
	{
		return (std::string&) __agent_name;
	}
	

public: // setters

	inline void team_nickname(const std::string &team_nickname)
	{
		__team_nickname = team_nickname;
		has_team_nickname(true);
	}
	
	inline void agent_name(const std::string &agent_name)
	{
		__agent_name = agent_name;
		has_agent_name(true);
	}
	

public: // has_attribute getters

	inline bool has_team_nickname() const
	{
		return __has_team_nickname;
	}
	
	inline bool has_agent_name() const
	{
		return __has_agent_name;
	}
	

public: // has_attribute setters

	inline void has_team_nickname(const bool &has_team_nickname)
	{
		__has_team_nickname = has_team_nickname;
	}
	
	inline void has_agent_name(const bool &has_agent_name)
	{
		__has_agent_name = has_agent_name;
	}
	

public:

	JoinOfflineGame()
	{
		has_team_nickname(false);
		has_agent_name(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "JoinOfflineGame";
	}
	
	virtual inline const std::string name() const
	{
		return "JoinOfflineGame";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize team_nickname
		s += __has_team_nickname;
		if (__has_team_nickname)
		{
			std::string tmp20 = "";
			unsigned int tmp22 = __team_nickname.size();
			auto tmp23 = reinterpret_cast<char*>(&tmp22);
			tmp20 += std::string(tmp23, sizeof(unsigned int));
			while (tmp20.size() && tmp20.back() == 0)
				tmp20.pop_back();
			unsigned char tmp25 = tmp20.size();
			auto tmp26 = reinterpret_cast<char*>(&tmp25);
			s += std::string(tmp26, sizeof(unsigned char));
			s += tmp20;
			
			s += __team_nickname;
		}
		
		// serialize agent_name
		s += __has_agent_name;
		if (__has_agent_name)
		{
			std::string tmp27 = "";
			unsigned int tmp29 = __agent_name.size();
			auto tmp30 = reinterpret_cast<char*>(&tmp29);
			tmp27 += std::string(tmp30, sizeof(unsigned int));
			while (tmp27.size() && tmp27.back() == 0)
				tmp27.pop_back();
			unsigned char tmp32 = tmp27.size();
			auto tmp33 = reinterpret_cast<char*>(&tmp32);
			s += std::string(tmp33, sizeof(unsigned char));
			s += tmp27;
			
			s += __agent_name;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize team_nickname
		__has_team_nickname = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_team_nickname)
		{
			unsigned char tmp34;
			tmp34 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp35 = std::string(&s[offset], tmp34);
			offset += tmp34;
			while (tmp35.size() < sizeof(unsigned int))
				tmp35 += '\x00';
			unsigned int tmp36;
			tmp36 = *((unsigned int*) (&tmp35[0]));
			
			__team_nickname = s.substr(offset, tmp36);
			offset += tmp36;
		}
		
		// deserialize agent_name
		__has_agent_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_agent_name)
		{
			unsigned char tmp37;
			tmp37 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp38 = std::string(&s[offset], tmp37);
			offset += tmp37;
			while (tmp38.size() < sizeof(unsigned int))
				tmp38 += '\x00';
			unsigned int tmp39;
			tmp39 = *((unsigned int*) (&tmp38[0]));
			
			__agent_name = s.substr(offset, tmp39);
			offset += tmp39;
		}
		
		return offset;
	}
};


class JoinOnlineGame : public KSObject
{

protected:

	std::string __token;
	std::string __agent_name;

	bool __has_token;
	bool __has_agent_name;


public: // getters

	inline std::string token() const
	{
		return __token;
	}
	
	inline std::string agent_name() const
	{
		return __agent_name;
	}
	

public: // reference getters

	inline std::string &ref_token() const
	{
		return (std::string&) __token;
	}
	
	inline std::string &ref_agent_name() const
	{
		return (std::string&) __agent_name;
	}
	

public: // setters

	inline void token(const std::string &token)
	{
		__token = token;
		has_token(true);
	}
	
	inline void agent_name(const std::string &agent_name)
	{
		__agent_name = agent_name;
		has_agent_name(true);
	}
	

public: // has_attribute getters

	inline bool has_token() const
	{
		return __has_token;
	}
	
	inline bool has_agent_name() const
	{
		return __has_agent_name;
	}
	

public: // has_attribute setters

	inline void has_token(const bool &has_token)
	{
		__has_token = has_token;
	}
	
	inline void has_agent_name(const bool &has_agent_name)
	{
		__has_agent_name = has_agent_name;
	}
	

public:

	JoinOnlineGame()
	{
		has_token(false);
		has_agent_name(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "JoinOnlineGame";
	}
	
	virtual inline const std::string name() const
	{
		return "JoinOnlineGame";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize token
		s += __has_token;
		if (__has_token)
		{
			std::string tmp40 = "";
			unsigned int tmp42 = __token.size();
			auto tmp43 = reinterpret_cast<char*>(&tmp42);
			tmp40 += std::string(tmp43, sizeof(unsigned int));
			while (tmp40.size() && tmp40.back() == 0)
				tmp40.pop_back();
			unsigned char tmp45 = tmp40.size();
			auto tmp46 = reinterpret_cast<char*>(&tmp45);
			s += std::string(tmp46, sizeof(unsigned char));
			s += tmp40;
			
			s += __token;
		}
		
		// serialize agent_name
		s += __has_agent_name;
		if (__has_agent_name)
		{
			std::string tmp47 = "";
			unsigned int tmp49 = __agent_name.size();
			auto tmp50 = reinterpret_cast<char*>(&tmp49);
			tmp47 += std::string(tmp50, sizeof(unsigned int));
			while (tmp47.size() && tmp47.back() == 0)
				tmp47.pop_back();
			unsigned char tmp52 = tmp47.size();
			auto tmp53 = reinterpret_cast<char*>(&tmp52);
			s += std::string(tmp53, sizeof(unsigned char));
			s += tmp47;
			
			s += __agent_name;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize token
		__has_token = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_token)
		{
			unsigned char tmp54;
			tmp54 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp55 = std::string(&s[offset], tmp54);
			offset += tmp54;
			while (tmp55.size() < sizeof(unsigned int))
				tmp55 += '\x00';
			unsigned int tmp56;
			tmp56 = *((unsigned int*) (&tmp55[0]));
			
			__token = s.substr(offset, tmp56);
			offset += tmp56;
		}
		
		// deserialize agent_name
		__has_agent_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_agent_name)
		{
			unsigned char tmp57;
			tmp57 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp58 = std::string(&s[offset], tmp57);
			offset += tmp57;
			while (tmp58.size() < sizeof(unsigned int))
				tmp58 += '\x00';
			unsigned int tmp59;
			tmp59 = *((unsigned int*) (&tmp58[0]));
			
			__agent_name = s.substr(offset, tmp59);
			offset += tmp59;
		}
		
		return offset;
	}
};


class ClientJoined : public KSObject
{

protected:

	bool __joined;
	std::string __side_name;
	std::map<std::string, std::vector<std::string>> __sides;

	bool __has_joined;
	bool __has_side_name;
	bool __has_sides;


public: // getters

	inline bool joined() const
	{
		return __joined;
	}
	
	inline std::string side_name() const
	{
		return __side_name;
	}
	
	inline std::map<std::string, std::vector<std::string>> sides() const
	{
		return __sides;
	}
	

public: // reference getters

	inline bool &ref_joined() const
	{
		return (bool&) __joined;
	}
	
	inline std::string &ref_side_name() const
	{
		return (std::string&) __side_name;
	}
	
	inline std::map<std::string, std::vector<std::string>> &ref_sides() const
	{
		return (std::map<std::string, std::vector<std::string>>&) __sides;
	}
	

public: // setters

	inline void joined(const bool &joined)
	{
		__joined = joined;
		has_joined(true);
	}
	
	inline void side_name(const std::string &side_name)
	{
		__side_name = side_name;
		has_side_name(true);
	}
	
	inline void sides(const std::map<std::string, std::vector<std::string>> &sides)
	{
		__sides = sides;
		has_sides(true);
	}
	

public: // has_attribute getters

	inline bool has_joined() const
	{
		return __has_joined;
	}
	
	inline bool has_side_name() const
	{
		return __has_side_name;
	}
	
	inline bool has_sides() const
	{
		return __has_sides;
	}
	

public: // has_attribute setters

	inline void has_joined(const bool &has_joined)
	{
		__has_joined = has_joined;
	}
	
	inline void has_side_name(const bool &has_side_name)
	{
		__has_side_name = has_side_name;
	}
	
	inline void has_sides(const bool &has_sides)
	{
		__has_sides = has_sides;
	}
	

public:

	ClientJoined()
	{
		has_joined(false);
		has_side_name(false);
		has_sides(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "ClientJoined";
	}
	
	virtual inline const std::string name() const
	{
		return "ClientJoined";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize joined
		s += __has_joined;
		if (__has_joined)
		{
			bool tmp61 = __joined;
			auto tmp62 = reinterpret_cast<char*>(&tmp61);
			s += std::string(tmp62, sizeof(bool));
		}
		
		// serialize side_name
		s += __has_side_name;
		if (__has_side_name)
		{
			std::string tmp63 = "";
			unsigned int tmp65 = __side_name.size();
			auto tmp66 = reinterpret_cast<char*>(&tmp65);
			tmp63 += std::string(tmp66, sizeof(unsigned int));
			while (tmp63.size() && tmp63.back() == 0)
				tmp63.pop_back();
			unsigned char tmp68 = tmp63.size();
			auto tmp69 = reinterpret_cast<char*>(&tmp68);
			s += std::string(tmp69, sizeof(unsigned char));
			s += tmp63;
			
			s += __side_name;
		}
		
		// serialize sides
		s += __has_sides;
		if (__has_sides)
		{
			std::string tmp70 = "";
			unsigned int tmp72 = __sides.size();
			auto tmp73 = reinterpret_cast<char*>(&tmp72);
			tmp70 += std::string(tmp73, sizeof(unsigned int));
			while (tmp70.size() && tmp70.back() == 0)
				tmp70.pop_back();
			unsigned char tmp75 = tmp70.size();
			auto tmp76 = reinterpret_cast<char*>(&tmp75);
			s += std::string(tmp76, sizeof(unsigned char));
			s += tmp70;
			
			for (auto &tmp77 : __sides)
			{
				s += '\x01';
				std::string tmp78 = "";
				unsigned int tmp80 = tmp77.first.size();
				auto tmp81 = reinterpret_cast<char*>(&tmp80);
				tmp78 += std::string(tmp81, sizeof(unsigned int));
				while (tmp78.size() && tmp78.back() == 0)
					tmp78.pop_back();
				unsigned char tmp83 = tmp78.size();
				auto tmp84 = reinterpret_cast<char*>(&tmp83);
				s += std::string(tmp84, sizeof(unsigned char));
				s += tmp78;
				
				s += tmp77.first;
				
				s += '\x01';
				std::string tmp85 = "";
				unsigned int tmp87 = tmp77.second.size();
				auto tmp88 = reinterpret_cast<char*>(&tmp87);
				tmp85 += std::string(tmp88, sizeof(unsigned int));
				while (tmp85.size() && tmp85.back() == 0)
					tmp85.pop_back();
				unsigned char tmp90 = tmp85.size();
				auto tmp91 = reinterpret_cast<char*>(&tmp90);
				s += std::string(tmp91, sizeof(unsigned char));
				s += tmp85;
				
				for (auto &tmp92 : tmp77.second)
				{
					s += '\x01';
					std::string tmp93 = "";
					unsigned int tmp95 = tmp92.size();
					auto tmp96 = reinterpret_cast<char*>(&tmp95);
					tmp93 += std::string(tmp96, sizeof(unsigned int));
					while (tmp93.size() && tmp93.back() == 0)
						tmp93.pop_back();
					unsigned char tmp98 = tmp93.size();
					auto tmp99 = reinterpret_cast<char*>(&tmp98);
					s += std::string(tmp99, sizeof(unsigned char));
					s += tmp93;
					
					s += tmp92;
				}
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize joined
		__has_joined = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_joined)
		{
			__joined = *((bool*) (&s[offset]));
			offset += sizeof(bool);
		}
		
		// deserialize side_name
		__has_side_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_side_name)
		{
			unsigned char tmp100;
			tmp100 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp101 = std::string(&s[offset], tmp100);
			offset += tmp100;
			while (tmp101.size() < sizeof(unsigned int))
				tmp101 += '\x00';
			unsigned int tmp102;
			tmp102 = *((unsigned int*) (&tmp101[0]));
			
			__side_name = s.substr(offset, tmp102);
			offset += tmp102;
		}
		
		// deserialize sides
		__has_sides = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_sides)
		{
			unsigned char tmp103;
			tmp103 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp104 = std::string(&s[offset], tmp103);
			offset += tmp103;
			while (tmp104.size() < sizeof(unsigned int))
				tmp104 += '\x00';
			unsigned int tmp105;
			tmp105 = *((unsigned int*) (&tmp104[0]));
			
			__sides.clear();
			for (unsigned int tmp106 = 0; tmp106 < tmp105; tmp106++)
			{
				std::string tmp107;
				offset++;
				unsigned char tmp109;
				tmp109 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp110 = std::string(&s[offset], tmp109);
				offset += tmp109;
				while (tmp110.size() < sizeof(unsigned int))
					tmp110 += '\x00';
				unsigned int tmp111;
				tmp111 = *((unsigned int*) (&tmp110[0]));
				
				tmp107 = s.substr(offset, tmp111);
				offset += tmp111;
				
				std::vector<std::string> tmp108;
				offset++;
				unsigned char tmp112;
				tmp112 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp113 = std::string(&s[offset], tmp112);
				offset += tmp112;
				while (tmp113.size() < sizeof(unsigned int))
					tmp113 += '\x00';
				unsigned int tmp114;
				tmp114 = *((unsigned int*) (&tmp113[0]));
				
				tmp108.clear();
				for (unsigned int tmp115 = 0; tmp115 < tmp114; tmp115++)
				{
					std::string tmp116;
					offset++;
					unsigned char tmp117;
					tmp117 = *((unsigned char*) (&s[offset]));
					offset += sizeof(unsigned char);
					std::string tmp118 = std::string(&s[offset], tmp117);
					offset += tmp117;
					while (tmp118.size() < sizeof(unsigned int))
						tmp118 += '\x00';
					unsigned int tmp119;
					tmp119 = *((unsigned int*) (&tmp118[0]));
					
					tmp116 = s.substr(offset, tmp119);
					offset += tmp119;
					tmp108.push_back(tmp116);
				}
				
				__sides[tmp107] = tmp108;
			}
		}
		
		return offset;
	}
};


class AgentJoined : public KSObject
{

protected:

	std::string __side_name;
	std::string __agent_name;
	std::string __team_nickname;

	bool __has_side_name;
	bool __has_agent_name;
	bool __has_team_nickname;


public: // getters

	inline std::string side_name() const
	{
		return __side_name;
	}
	
	inline std::string agent_name() const
	{
		return __agent_name;
	}
	
	inline std::string team_nickname() const
	{
		return __team_nickname;
	}
	

public: // reference getters

	inline std::string &ref_side_name() const
	{
		return (std::string&) __side_name;
	}
	
	inline std::string &ref_agent_name() const
	{
		return (std::string&) __agent_name;
	}
	
	inline std::string &ref_team_nickname() const
	{
		return (std::string&) __team_nickname;
	}
	

public: // setters

	inline void side_name(const std::string &side_name)
	{
		__side_name = side_name;
		has_side_name(true);
	}
	
	inline void agent_name(const std::string &agent_name)
	{
		__agent_name = agent_name;
		has_agent_name(true);
	}
	
	inline void team_nickname(const std::string &team_nickname)
	{
		__team_nickname = team_nickname;
		has_team_nickname(true);
	}
	

public: // has_attribute getters

	inline bool has_side_name() const
	{
		return __has_side_name;
	}
	
	inline bool has_agent_name() const
	{
		return __has_agent_name;
	}
	
	inline bool has_team_nickname() const
	{
		return __has_team_nickname;
	}
	

public: // has_attribute setters

	inline void has_side_name(const bool &has_side_name)
	{
		__has_side_name = has_side_name;
	}
	
	inline void has_agent_name(const bool &has_agent_name)
	{
		__has_agent_name = has_agent_name;
	}
	
	inline void has_team_nickname(const bool &has_team_nickname)
	{
		__has_team_nickname = has_team_nickname;
	}
	

public:

	AgentJoined()
	{
		has_side_name(false);
		has_agent_name(false);
		has_team_nickname(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "AgentJoined";
	}
	
	virtual inline const std::string name() const
	{
		return "AgentJoined";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize side_name
		s += __has_side_name;
		if (__has_side_name)
		{
			std::string tmp120 = "";
			unsigned int tmp122 = __side_name.size();
			auto tmp123 = reinterpret_cast<char*>(&tmp122);
			tmp120 += std::string(tmp123, sizeof(unsigned int));
			while (tmp120.size() && tmp120.back() == 0)
				tmp120.pop_back();
			unsigned char tmp125 = tmp120.size();
			auto tmp126 = reinterpret_cast<char*>(&tmp125);
			s += std::string(tmp126, sizeof(unsigned char));
			s += tmp120;
			
			s += __side_name;
		}
		
		// serialize agent_name
		s += __has_agent_name;
		if (__has_agent_name)
		{
			std::string tmp127 = "";
			unsigned int tmp129 = __agent_name.size();
			auto tmp130 = reinterpret_cast<char*>(&tmp129);
			tmp127 += std::string(tmp130, sizeof(unsigned int));
			while (tmp127.size() && tmp127.back() == 0)
				tmp127.pop_back();
			unsigned char tmp132 = tmp127.size();
			auto tmp133 = reinterpret_cast<char*>(&tmp132);
			s += std::string(tmp133, sizeof(unsigned char));
			s += tmp127;
			
			s += __agent_name;
		}
		
		// serialize team_nickname
		s += __has_team_nickname;
		if (__has_team_nickname)
		{
			std::string tmp134 = "";
			unsigned int tmp136 = __team_nickname.size();
			auto tmp137 = reinterpret_cast<char*>(&tmp136);
			tmp134 += std::string(tmp137, sizeof(unsigned int));
			while (tmp134.size() && tmp134.back() == 0)
				tmp134.pop_back();
			unsigned char tmp139 = tmp134.size();
			auto tmp140 = reinterpret_cast<char*>(&tmp139);
			s += std::string(tmp140, sizeof(unsigned char));
			s += tmp134;
			
			s += __team_nickname;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize side_name
		__has_side_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_side_name)
		{
			unsigned char tmp141;
			tmp141 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp142 = std::string(&s[offset], tmp141);
			offset += tmp141;
			while (tmp142.size() < sizeof(unsigned int))
				tmp142 += '\x00';
			unsigned int tmp143;
			tmp143 = *((unsigned int*) (&tmp142[0]));
			
			__side_name = s.substr(offset, tmp143);
			offset += tmp143;
		}
		
		// deserialize agent_name
		__has_agent_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_agent_name)
		{
			unsigned char tmp144;
			tmp144 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp145 = std::string(&s[offset], tmp144);
			offset += tmp144;
			while (tmp145.size() < sizeof(unsigned int))
				tmp145 += '\x00';
			unsigned int tmp146;
			tmp146 = *((unsigned int*) (&tmp145[0]));
			
			__agent_name = s.substr(offset, tmp146);
			offset += tmp146;
		}
		
		// deserialize team_nickname
		__has_team_nickname = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_team_nickname)
		{
			unsigned char tmp147;
			tmp147 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp148 = std::string(&s[offset], tmp147);
			offset += tmp147;
			while (tmp148.size() < sizeof(unsigned int))
				tmp148 += '\x00';
			unsigned int tmp149;
			tmp149 = *((unsigned int*) (&tmp148[0]));
			
			__team_nickname = s.substr(offset, tmp149);
			offset += tmp149;
		}
		
		return offset;
	}
};


class AgentLeft : public KSObject
{

protected:

	std::string __side_name;
	std::string __agent_name;

	bool __has_side_name;
	bool __has_agent_name;


public: // getters

	inline std::string side_name() const
	{
		return __side_name;
	}
	
	inline std::string agent_name() const
	{
		return __agent_name;
	}
	

public: // reference getters

	inline std::string &ref_side_name() const
	{
		return (std::string&) __side_name;
	}
	
	inline std::string &ref_agent_name() const
	{
		return (std::string&) __agent_name;
	}
	

public: // setters

	inline void side_name(const std::string &side_name)
	{
		__side_name = side_name;
		has_side_name(true);
	}
	
	inline void agent_name(const std::string &agent_name)
	{
		__agent_name = agent_name;
		has_agent_name(true);
	}
	

public: // has_attribute getters

	inline bool has_side_name() const
	{
		return __has_side_name;
	}
	
	inline bool has_agent_name() const
	{
		return __has_agent_name;
	}
	

public: // has_attribute setters

	inline void has_side_name(const bool &has_side_name)
	{
		__has_side_name = has_side_name;
	}
	
	inline void has_agent_name(const bool &has_agent_name)
	{
		__has_agent_name = has_agent_name;
	}
	

public:

	AgentLeft()
	{
		has_side_name(false);
		has_agent_name(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "AgentLeft";
	}
	
	virtual inline const std::string name() const
	{
		return "AgentLeft";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize side_name
		s += __has_side_name;
		if (__has_side_name)
		{
			std::string tmp150 = "";
			unsigned int tmp152 = __side_name.size();
			auto tmp153 = reinterpret_cast<char*>(&tmp152);
			tmp150 += std::string(tmp153, sizeof(unsigned int));
			while (tmp150.size() && tmp150.back() == 0)
				tmp150.pop_back();
			unsigned char tmp155 = tmp150.size();
			auto tmp156 = reinterpret_cast<char*>(&tmp155);
			s += std::string(tmp156, sizeof(unsigned char));
			s += tmp150;
			
			s += __side_name;
		}
		
		// serialize agent_name
		s += __has_agent_name;
		if (__has_agent_name)
		{
			std::string tmp157 = "";
			unsigned int tmp159 = __agent_name.size();
			auto tmp160 = reinterpret_cast<char*>(&tmp159);
			tmp157 += std::string(tmp160, sizeof(unsigned int));
			while (tmp157.size() && tmp157.back() == 0)
				tmp157.pop_back();
			unsigned char tmp162 = tmp157.size();
			auto tmp163 = reinterpret_cast<char*>(&tmp162);
			s += std::string(tmp163, sizeof(unsigned char));
			s += tmp157;
			
			s += __agent_name;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize side_name
		__has_side_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_side_name)
		{
			unsigned char tmp164;
			tmp164 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp165 = std::string(&s[offset], tmp164);
			offset += tmp164;
			while (tmp165.size() < sizeof(unsigned int))
				tmp165 += '\x00';
			unsigned int tmp166;
			tmp166 = *((unsigned int*) (&tmp165[0]));
			
			__side_name = s.substr(offset, tmp166);
			offset += tmp166;
		}
		
		// deserialize agent_name
		__has_agent_name = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_agent_name)
		{
			unsigned char tmp167;
			tmp167 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp168 = std::string(&s[offset], tmp167);
			offset += tmp167;
			while (tmp168.size() < sizeof(unsigned int))
				tmp168 += '\x00';
			unsigned int tmp169;
			tmp169 = *((unsigned int*) (&tmp168[0]));
			
			__agent_name = s.substr(offset, tmp169);
			offset += tmp169;
		}
		
		return offset;
	}
};


class StartGame : public KSObject
{

protected:

	unsigned int __start_time;

	bool __has_start_time;


public: // getters

	inline unsigned int start_time() const
	{
		return __start_time;
	}
	

public: // reference getters

	inline unsigned int &ref_start_time() const
	{
		return (unsigned int&) __start_time;
	}
	

public: // setters

	inline void start_time(const unsigned int &start_time)
	{
		__start_time = start_time;
		has_start_time(true);
	}
	

public: // has_attribute getters

	inline bool has_start_time() const
	{
		return __has_start_time;
	}
	

public: // has_attribute setters

	inline void has_start_time(const bool &has_start_time)
	{
		__has_start_time = has_start_time;
	}
	

public:

	StartGame()
	{
		has_start_time(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "StartGame";
	}
	
	virtual inline const std::string name() const
	{
		return "StartGame";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize start_time
		s += __has_start_time;
		if (__has_start_time)
		{
			unsigned int tmp171 = __start_time;
			auto tmp172 = reinterpret_cast<char*>(&tmp171);
			s += std::string(tmp172, sizeof(unsigned int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize start_time
		__has_start_time = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_start_time)
		{
			__start_time = *((unsigned int*) (&s[offset]));
			offset += sizeof(unsigned int);
		}
		
		return offset;
	}
};


class EndGame : public KSObject
{

protected:

	std::string __winner_sidename;
	std::map<std::string, std::map<std::string, std::string>> __details;

	bool __has_winner_sidename;
	bool __has_details;


public: // getters

	inline std::string winner_sidename() const
	{
		return __winner_sidename;
	}
	
	inline std::map<std::string, std::map<std::string, std::string>> details() const
	{
		return __details;
	}
	

public: // reference getters

	inline std::string &ref_winner_sidename() const
	{
		return (std::string&) __winner_sidename;
	}
	
	inline std::map<std::string, std::map<std::string, std::string>> &ref_details() const
	{
		return (std::map<std::string, std::map<std::string, std::string>>&) __details;
	}
	

public: // setters

	inline void winner_sidename(const std::string &winner_sidename)
	{
		__winner_sidename = winner_sidename;
		has_winner_sidename(true);
	}
	
	inline void details(const std::map<std::string, std::map<std::string, std::string>> &details)
	{
		__details = details;
		has_details(true);
	}
	

public: // has_attribute getters

	inline bool has_winner_sidename() const
	{
		return __has_winner_sidename;
	}
	
	inline bool has_details() const
	{
		return __has_details;
	}
	

public: // has_attribute setters

	inline void has_winner_sidename(const bool &has_winner_sidename)
	{
		__has_winner_sidename = has_winner_sidename;
	}
	
	inline void has_details(const bool &has_details)
	{
		__has_details = has_details;
	}
	

public:

	EndGame()
	{
		has_winner_sidename(false);
		has_details(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "EndGame";
	}
	
	virtual inline const std::string name() const
	{
		return "EndGame";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize winner_sidename
		s += __has_winner_sidename;
		if (__has_winner_sidename)
		{
			std::string tmp173 = "";
			unsigned int tmp175 = __winner_sidename.size();
			auto tmp176 = reinterpret_cast<char*>(&tmp175);
			tmp173 += std::string(tmp176, sizeof(unsigned int));
			while (tmp173.size() && tmp173.back() == 0)
				tmp173.pop_back();
			unsigned char tmp178 = tmp173.size();
			auto tmp179 = reinterpret_cast<char*>(&tmp178);
			s += std::string(tmp179, sizeof(unsigned char));
			s += tmp173;
			
			s += __winner_sidename;
		}
		
		// serialize details
		s += __has_details;
		if (__has_details)
		{
			std::string tmp180 = "";
			unsigned int tmp182 = __details.size();
			auto tmp183 = reinterpret_cast<char*>(&tmp182);
			tmp180 += std::string(tmp183, sizeof(unsigned int));
			while (tmp180.size() && tmp180.back() == 0)
				tmp180.pop_back();
			unsigned char tmp185 = tmp180.size();
			auto tmp186 = reinterpret_cast<char*>(&tmp185);
			s += std::string(tmp186, sizeof(unsigned char));
			s += tmp180;
			
			for (auto &tmp187 : __details)
			{
				s += '\x01';
				std::string tmp188 = "";
				unsigned int tmp190 = tmp187.first.size();
				auto tmp191 = reinterpret_cast<char*>(&tmp190);
				tmp188 += std::string(tmp191, sizeof(unsigned int));
				while (tmp188.size() && tmp188.back() == 0)
					tmp188.pop_back();
				unsigned char tmp193 = tmp188.size();
				auto tmp194 = reinterpret_cast<char*>(&tmp193);
				s += std::string(tmp194, sizeof(unsigned char));
				s += tmp188;
				
				s += tmp187.first;
				
				s += '\x01';
				std::string tmp195 = "";
				unsigned int tmp197 = tmp187.second.size();
				auto tmp198 = reinterpret_cast<char*>(&tmp197);
				tmp195 += std::string(tmp198, sizeof(unsigned int));
				while (tmp195.size() && tmp195.back() == 0)
					tmp195.pop_back();
				unsigned char tmp200 = tmp195.size();
				auto tmp201 = reinterpret_cast<char*>(&tmp200);
				s += std::string(tmp201, sizeof(unsigned char));
				s += tmp195;
				
				for (auto &tmp202 : tmp187.second)
				{
					s += '\x01';
					std::string tmp203 = "";
					unsigned int tmp205 = tmp202.first.size();
					auto tmp206 = reinterpret_cast<char*>(&tmp205);
					tmp203 += std::string(tmp206, sizeof(unsigned int));
					while (tmp203.size() && tmp203.back() == 0)
						tmp203.pop_back();
					unsigned char tmp208 = tmp203.size();
					auto tmp209 = reinterpret_cast<char*>(&tmp208);
					s += std::string(tmp209, sizeof(unsigned char));
					s += tmp203;
					
					s += tmp202.first;
					
					s += '\x01';
					std::string tmp210 = "";
					unsigned int tmp212 = tmp202.second.size();
					auto tmp213 = reinterpret_cast<char*>(&tmp212);
					tmp210 += std::string(tmp213, sizeof(unsigned int));
					while (tmp210.size() && tmp210.back() == 0)
						tmp210.pop_back();
					unsigned char tmp215 = tmp210.size();
					auto tmp216 = reinterpret_cast<char*>(&tmp215);
					s += std::string(tmp216, sizeof(unsigned char));
					s += tmp210;
					
					s += tmp202.second;
				}
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize winner_sidename
		__has_winner_sidename = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_winner_sidename)
		{
			unsigned char tmp217;
			tmp217 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp218 = std::string(&s[offset], tmp217);
			offset += tmp217;
			while (tmp218.size() < sizeof(unsigned int))
				tmp218 += '\x00';
			unsigned int tmp219;
			tmp219 = *((unsigned int*) (&tmp218[0]));
			
			__winner_sidename = s.substr(offset, tmp219);
			offset += tmp219;
		}
		
		// deserialize details
		__has_details = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_details)
		{
			unsigned char tmp220;
			tmp220 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp221 = std::string(&s[offset], tmp220);
			offset += tmp220;
			while (tmp221.size() < sizeof(unsigned int))
				tmp221 += '\x00';
			unsigned int tmp222;
			tmp222 = *((unsigned int*) (&tmp221[0]));
			
			__details.clear();
			for (unsigned int tmp223 = 0; tmp223 < tmp222; tmp223++)
			{
				std::string tmp224;
				offset++;
				unsigned char tmp226;
				tmp226 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp227 = std::string(&s[offset], tmp226);
				offset += tmp226;
				while (tmp227.size() < sizeof(unsigned int))
					tmp227 += '\x00';
				unsigned int tmp228;
				tmp228 = *((unsigned int*) (&tmp227[0]));
				
				tmp224 = s.substr(offset, tmp228);
				offset += tmp228;
				
				std::map<std::string, std::string> tmp225;
				offset++;
				unsigned char tmp229;
				tmp229 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp230 = std::string(&s[offset], tmp229);
				offset += tmp229;
				while (tmp230.size() < sizeof(unsigned int))
					tmp230 += '\x00';
				unsigned int tmp231;
				tmp231 = *((unsigned int*) (&tmp230[0]));
				
				tmp225.clear();
				for (unsigned int tmp232 = 0; tmp232 < tmp231; tmp232++)
				{
					std::string tmp233;
					offset++;
					unsigned char tmp235;
					tmp235 = *((unsigned char*) (&s[offset]));
					offset += sizeof(unsigned char);
					std::string tmp236 = std::string(&s[offset], tmp235);
					offset += tmp235;
					while (tmp236.size() < sizeof(unsigned int))
						tmp236 += '\x00';
					unsigned int tmp237;
					tmp237 = *((unsigned int*) (&tmp236[0]));
					
					tmp233 = s.substr(offset, tmp237);
					offset += tmp237;
					
					std::string tmp234;
					offset++;
					unsigned char tmp238;
					tmp238 = *((unsigned char*) (&s[offset]));
					offset += sizeof(unsigned char);
					std::string tmp239 = std::string(&s[offset], tmp238);
					offset += tmp238;
					while (tmp239.size() < sizeof(unsigned int))
						tmp239 += '\x00';
					unsigned int tmp240;
					tmp240 = *((unsigned int*) (&tmp239[0]));
					
					tmp234 = s.substr(offset, tmp240);
					offset += tmp240;
					
					tmp225[tmp233] = tmp234;
				}
				
				__details[tmp224] = tmp225;
			}
		}
		
		return offset;
	}
};


class BaseSnapshot : public KSObject
{

protected:

	std::string __world_payload;

	bool __has_world_payload;


public: // getters

	inline std::string world_payload() const
	{
		return __world_payload;
	}
	

public: // reference getters

	inline std::string &ref_world_payload() const
	{
		return (std::string&) __world_payload;
	}
	

public: // setters

	inline void world_payload(const std::string &world_payload)
	{
		__world_payload = world_payload;
		has_world_payload(true);
	}
	

public: // has_attribute getters

	inline bool has_world_payload() const
	{
		return __has_world_payload;
	}
	

public: // has_attribute setters

	inline void has_world_payload(const bool &has_world_payload)
	{
		__has_world_payload = has_world_payload;
	}
	

public:

	BaseSnapshot()
	{
		has_world_payload(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "BaseSnapshot";
	}
	
	virtual inline const std::string name() const
	{
		return "BaseSnapshot";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize world_payload
		s += __has_world_payload;
		if (__has_world_payload)
		{
			std::string tmp241 = "";
			unsigned int tmp243 = __world_payload.size();
			auto tmp244 = reinterpret_cast<char*>(&tmp243);
			tmp241 += std::string(tmp244, sizeof(unsigned int));
			while (tmp241.size() && tmp241.back() == 0)
				tmp241.pop_back();
			unsigned char tmp246 = tmp241.size();
			auto tmp247 = reinterpret_cast<char*>(&tmp246);
			s += std::string(tmp247, sizeof(unsigned char));
			s += tmp241;
			
			s += __world_payload;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize world_payload
		__has_world_payload = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_world_payload)
		{
			unsigned char tmp248;
			tmp248 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp249 = std::string(&s[offset], tmp248);
			offset += tmp248;
			while (tmp249.size() < sizeof(unsigned int))
				tmp249 += '\x00';
			unsigned int tmp250;
			tmp250 = *((unsigned int*) (&tmp249[0]));
			
			__world_payload = s.substr(offset, tmp250);
			offset += tmp250;
		}
		
		return offset;
	}
};


class RealtimeSnapshot : public BaseSnapshot
{

protected:

	unsigned int __current_cycle;
	float __cycle_duration;

	bool __has_current_cycle;
	bool __has_cycle_duration;


public: // getters

	inline unsigned int current_cycle() const
	{
		return __current_cycle;
	}
	
	inline float cycle_duration() const
	{
		return __cycle_duration;
	}
	

public: // reference getters

	inline unsigned int &ref_current_cycle() const
	{
		return (unsigned int&) __current_cycle;
	}
	
	inline float &ref_cycle_duration() const
	{
		return (float&) __cycle_duration;
	}
	

public: // setters

	inline void current_cycle(const unsigned int &current_cycle)
	{
		__current_cycle = current_cycle;
		has_current_cycle(true);
	}
	
	inline void cycle_duration(const float &cycle_duration)
	{
		__cycle_duration = cycle_duration;
		has_cycle_duration(true);
	}
	

public: // has_attribute getters

	inline bool has_current_cycle() const
	{
		return __has_current_cycle;
	}
	
	inline bool has_cycle_duration() const
	{
		return __has_cycle_duration;
	}
	

public: // has_attribute setters

	inline void has_current_cycle(const bool &has_current_cycle)
	{
		__has_current_cycle = has_current_cycle;
	}
	
	inline void has_cycle_duration(const bool &has_cycle_duration)
	{
		__has_cycle_duration = has_cycle_duration;
	}
	

public:

	RealtimeSnapshot()
	{
		has_current_cycle(false);
		has_cycle_duration(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "RealtimeSnapshot";
	}
	
	virtual inline const std::string name() const
	{
		return "RealtimeSnapshot";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize parents
		s += BaseSnapshot::serialize();
		
		// serialize current_cycle
		s += __has_current_cycle;
		if (__has_current_cycle)
		{
			unsigned int tmp252 = __current_cycle;
			auto tmp253 = reinterpret_cast<char*>(&tmp252);
			s += std::string(tmp253, sizeof(unsigned int));
		}
		
		// serialize cycle_duration
		s += __has_cycle_duration;
		if (__has_cycle_duration)
		{
			float tmp255 = __cycle_duration;
			auto tmp256 = reinterpret_cast<char*>(&tmp255);
			s += std::string(tmp256, sizeof(float));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize parents
		offset = BaseSnapshot::deserialize(s, offset);
		
		// deserialize current_cycle
		__has_current_cycle = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_current_cycle)
		{
			__current_cycle = *((unsigned int*) (&s[offset]));
			offset += sizeof(unsigned int);
		}
		
		// deserialize cycle_duration
		__has_cycle_duration = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cycle_duration)
		{
			__cycle_duration = *((float*) (&s[offset]));
			offset += sizeof(float);
		}
		
		return offset;
	}
};


class TurnbasedSnapshot : public RealtimeSnapshot
{

protected:

	std::vector<std::string> __turn_allowed_sides;

	bool __has_turn_allowed_sides;


public: // getters

	inline std::vector<std::string> turn_allowed_sides() const
	{
		return __turn_allowed_sides;
	}
	

public: // reference getters

	inline std::vector<std::string> &ref_turn_allowed_sides() const
	{
		return (std::vector<std::string>&) __turn_allowed_sides;
	}
	

public: // setters

	inline void turn_allowed_sides(const std::vector<std::string> &turn_allowed_sides)
	{
		__turn_allowed_sides = turn_allowed_sides;
		has_turn_allowed_sides(true);
	}
	

public: // has_attribute getters

	inline bool has_turn_allowed_sides() const
	{
		return __has_turn_allowed_sides;
	}
	

public: // has_attribute setters

	inline void has_turn_allowed_sides(const bool &has_turn_allowed_sides)
	{
		__has_turn_allowed_sides = has_turn_allowed_sides;
	}
	

public:

	TurnbasedSnapshot()
	{
		has_turn_allowed_sides(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "TurnbasedSnapshot";
	}
	
	virtual inline const std::string name() const
	{
		return "TurnbasedSnapshot";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize parents
		s += RealtimeSnapshot::serialize();
		
		// serialize turn_allowed_sides
		s += __has_turn_allowed_sides;
		if (__has_turn_allowed_sides)
		{
			std::string tmp257 = "";
			unsigned int tmp259 = __turn_allowed_sides.size();
			auto tmp260 = reinterpret_cast<char*>(&tmp259);
			tmp257 += std::string(tmp260, sizeof(unsigned int));
			while (tmp257.size() && tmp257.back() == 0)
				tmp257.pop_back();
			unsigned char tmp262 = tmp257.size();
			auto tmp263 = reinterpret_cast<char*>(&tmp262);
			s += std::string(tmp263, sizeof(unsigned char));
			s += tmp257;
			
			for (auto &tmp264 : __turn_allowed_sides)
			{
				s += '\x01';
				std::string tmp265 = "";
				unsigned int tmp267 = tmp264.size();
				auto tmp268 = reinterpret_cast<char*>(&tmp267);
				tmp265 += std::string(tmp268, sizeof(unsigned int));
				while (tmp265.size() && tmp265.back() == 0)
					tmp265.pop_back();
				unsigned char tmp270 = tmp265.size();
				auto tmp271 = reinterpret_cast<char*>(&tmp270);
				s += std::string(tmp271, sizeof(unsigned char));
				s += tmp265;
				
				s += tmp264;
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize parents
		offset = RealtimeSnapshot::deserialize(s, offset);
		
		// deserialize turn_allowed_sides
		__has_turn_allowed_sides = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_turn_allowed_sides)
		{
			unsigned char tmp272;
			tmp272 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp273 = std::string(&s[offset], tmp272);
			offset += tmp272;
			while (tmp273.size() < sizeof(unsigned int))
				tmp273 += '\x00';
			unsigned int tmp274;
			tmp274 = *((unsigned int*) (&tmp273[0]));
			
			__turn_allowed_sides.clear();
			for (unsigned int tmp275 = 0; tmp275 < tmp274; tmp275++)
			{
				std::string tmp276;
				offset++;
				unsigned char tmp277;
				tmp277 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp278 = std::string(&s[offset], tmp277);
				offset += tmp277;
				while (tmp278.size() < sizeof(unsigned int))
					tmp278 += '\x00';
				unsigned int tmp279;
				tmp279 = *((unsigned int*) (&tmp278[0]));
				
				tmp276 = s.substr(offset, tmp279);
				offset += tmp279;
				__turn_allowed_sides.push_back(tmp276);
			}
		}
		
		return offset;
	}
};


class BaseCommand : public KSObject
{

protected:

	std::string __type;
	std::string __payload;

	bool __has_type;
	bool __has_payload;


public: // getters

	inline std::string type() const
	{
		return __type;
	}
	
	inline std::string payload() const
	{
		return __payload;
	}
	

public: // reference getters

	inline std::string &ref_type() const
	{
		return (std::string&) __type;
	}
	
	inline std::string &ref_payload() const
	{
		return (std::string&) __payload;
	}
	

public: // setters

	inline void type(const std::string &type)
	{
		__type = type;
		has_type(true);
	}
	
	inline void payload(const std::string &payload)
	{
		__payload = payload;
		has_payload(true);
	}
	

public: // has_attribute getters

	inline bool has_type() const
	{
		return __has_type;
	}
	
	inline bool has_payload() const
	{
		return __has_payload;
	}
	

public: // has_attribute setters

	inline void has_type(const bool &has_type)
	{
		__has_type = has_type;
	}
	
	inline void has_payload(const bool &has_payload)
	{
		__has_payload = has_payload;
	}
	

public:

	BaseCommand()
	{
		has_type(false);
		has_payload(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "BaseCommand";
	}
	
	virtual inline const std::string name() const
	{
		return "BaseCommand";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize type
		s += __has_type;
		if (__has_type)
		{
			std::string tmp280 = "";
			unsigned int tmp282 = __type.size();
			auto tmp283 = reinterpret_cast<char*>(&tmp282);
			tmp280 += std::string(tmp283, sizeof(unsigned int));
			while (tmp280.size() && tmp280.back() == 0)
				tmp280.pop_back();
			unsigned char tmp285 = tmp280.size();
			auto tmp286 = reinterpret_cast<char*>(&tmp285);
			s += std::string(tmp286, sizeof(unsigned char));
			s += tmp280;
			
			s += __type;
		}
		
		// serialize payload
		s += __has_payload;
		if (__has_payload)
		{
			std::string tmp287 = "";
			unsigned int tmp289 = __payload.size();
			auto tmp290 = reinterpret_cast<char*>(&tmp289);
			tmp287 += std::string(tmp290, sizeof(unsigned int));
			while (tmp287.size() && tmp287.back() == 0)
				tmp287.pop_back();
			unsigned char tmp292 = tmp287.size();
			auto tmp293 = reinterpret_cast<char*>(&tmp292);
			s += std::string(tmp293, sizeof(unsigned char));
			s += tmp287;
			
			s += __payload;
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize type
		__has_type = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_type)
		{
			unsigned char tmp294;
			tmp294 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp295 = std::string(&s[offset], tmp294);
			offset += tmp294;
			while (tmp295.size() < sizeof(unsigned int))
				tmp295 += '\x00';
			unsigned int tmp296;
			tmp296 = *((unsigned int*) (&tmp295[0]));
			
			__type = s.substr(offset, tmp296);
			offset += tmp296;
		}
		
		// deserialize payload
		__has_payload = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_payload)
		{
			unsigned char tmp297;
			tmp297 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp298 = std::string(&s[offset], tmp297);
			offset += tmp297;
			while (tmp298.size() < sizeof(unsigned int))
				tmp298 += '\x00';
			unsigned int tmp299;
			tmp299 = *((unsigned int*) (&tmp298[0]));
			
			__payload = s.substr(offset, tmp299);
			offset += tmp299;
		}
		
		return offset;
	}
};


class RealtimeCommand : public BaseCommand
{

protected:

	unsigned int __cycle;

	bool __has_cycle;


public: // getters

	inline unsigned int cycle() const
	{
		return __cycle;
	}
	

public: // reference getters

	inline unsigned int &ref_cycle() const
	{
		return (unsigned int&) __cycle;
	}
	

public: // setters

	inline void cycle(const unsigned int &cycle)
	{
		__cycle = cycle;
		has_cycle(true);
	}
	

public: // has_attribute getters

	inline bool has_cycle() const
	{
		return __has_cycle;
	}
	

public: // has_attribute setters

	inline void has_cycle(const bool &has_cycle)
	{
		__has_cycle = has_cycle;
	}
	

public:

	RealtimeCommand()
	{
		has_cycle(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "RealtimeCommand";
	}
	
	virtual inline const std::string name() const
	{
		return "RealtimeCommand";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize parents
		s += BaseCommand::serialize();
		
		// serialize cycle
		s += __has_cycle;
		if (__has_cycle)
		{
			unsigned int tmp301 = __cycle;
			auto tmp302 = reinterpret_cast<char*>(&tmp301);
			s += std::string(tmp302, sizeof(unsigned int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize parents
		offset = BaseCommand::deserialize(s, offset);
		
		// deserialize cycle
		__has_cycle = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cycle)
		{
			__cycle = *((unsigned int*) (&s[offset]));
			offset += sizeof(unsigned int);
		}
		
		return offset;
	}
};


class TurnbasedCommand : public RealtimeCommand
{

protected:




public: // getters


public: // reference getters


public: // setters


public: // has_attribute getters


public: // has_attribute setters


public:

	TurnbasedCommand()
	{
	}
	
	static inline const std::string nameStatic()
	{
		return "TurnbasedCommand";
	}
	
	virtual inline const std::string name() const
	{
		return "TurnbasedCommand";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize parents
		s += RealtimeCommand::serialize();
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize parents
		offset = RealtimeCommand::deserialize(s, offset);
		
		return offset;
	}
};

} // namespace messages

} // namespace ks

#endif // _KS_MESSAGES_H_
