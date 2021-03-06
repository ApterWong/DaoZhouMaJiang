#ifndef MJ_ANALYRESULT_H
#define MJ_ANALYRESULT_H

#include <list>

#define DEBUG

class MJ_Player;
class MJ_AnalyResult
{
    friend class MJ_Player;
public:
    typedef char CARD;
    enum HU{
            //   总计26中胡法
            //    1番
            HU_PingHu		= 0x00,					//  平胡
            HU_QiangGang 	= 0x01,					//	抢杠
            HU_GangShangHua = 0x02,					//  杠上开花
            //    2番
            HU_ZiMo			= 0x04,						//  自摸
            HU_MenQianQing	= 0x08,						//  门清
            HU_XiaoDao	 	= 0x10,						//  小道
            HU_YouYiTao		= 0x20,						//  有一套
            HU_QiaoQiDui	= 0x40,						//  巧七对
            HU_ShiSanLang	= 0x80,						//	十三浪
            HU_YiTiaoLong	= 0x0100,					//  一条龙
            HU_HunYiSe		= 0x0200,					//  混一色
            HU_PengpengHu	= 0x0400,					//  碰碰胡
            HU_SiGuiYi		= 0x0800,					//  四归一
            HU_QuanQiuYi	= 0x1000,					//  全求一
            HU_DanWangZhua	= 0x2000,					//  单王抓
            HU_WangGuiWei	= 0x4000,					//  王归位
            //    4番
            HU_DaDao		= 0x8000,					//   大道
            HU_YouLiangTao	= 0x010000,					//   有两套
            HU_QiFengHui	= 0x020000,					//	 七风会
            HU_ShuangWangGuiWei = 0x040000,				//   双王归位
            HU_DanWangZhuaWang  = 0x080000,				//   单王抓王
            HU_ShuangWangZhua	= 0x100000,				//   双王抓
            HU_QingYiSe			= 0x200000,             // 清一色
            //    8番
            HU_ShuangWangZhuaWang = 0x400000,				//   双王抓王
            HU_SanWangGuiWei	  = 0x800000,				//   三王归位
            //  16 番
            //			不明白这种胡法	*/
            HU_SiWangGuiWei	 	  = 0x01000000				//   四王归位
        };

    enum HU_FLAG{
        F_JiePao = 0,       // 接炮
        F_ZiMo = 1,         // 自摸
        F_QiangGang = 2,    // 抢杠胡
        F_GangShangHua = 4  // 杠上开花
    };

public:
    MJ_AnalyResult();
    MJ_AnalyResult(MJ_Player &);

    ~MJ_AnalyResult();

    int canHu(CARD *);//返回可听牌集合

    int addHu(HU _HU);
    int calc_BeiShu(const MJ_Player &, CARD card, HU_FLAG flag/*自摸、接炮、抢杠、杠上花、*/);//计算多少翻

    int H_ShiSanLang(CARD *);     // 十三浪
    int H_QiFengHui(CARD *);      // 七风会
    int H_QiaoQiDui(CARD *);      // 七巧对

    std::list<const char *> HU_names();
    int getFan();

private:
    void analy_sort(CARD *li, int len);

private:
    int st_count;
    int sl_count;
    int dz_count;
    int el_count;
    int kz_count;
    int dan_count;
    int w_count;
    int g_count;
    int p_count;
    int c_count;
    int flag;
    int fan;

    CARD _w;
    CARD gang[4];
    CARD peng[4];
    CARD chi[4];
    CARD st[4];
    CARD sl[4];
    CARD dz[8];
    CARD el[8];
    CARD kz[8];
    CARD dan[16];

    static const char *HuNames[32];

#ifdef DEBUG
public:
    void printResult();
#endif
};

#define forin_dz(dz, Count, into, cur, w) do{ \
    for(auto i=0; i<(Count); i++) \
    {\
        ((dz)[i]!=(w) && ((into)[(cur)++] = (dz)[i])) || ((into)[(cur)++] = (w)); \
    }}while(0);

#define forin_el(el, Count, into, cur, w) do{ \
    for(auto i=0; i<(Count); i++) \
    {\
        if(isMJCARD(el[i] + 1)) \
            (((el)[i]+1) != w && ((into)[(cur)++] = (el)[i]+1)) || (((into)[(cur)++] = w)); \
        if(isMJCARD(el[i] - 2)) \
            ((((el)[i]-2) != w) && ((into)[(cur)++] = (el)[i]-2)) || ((into)[(cur)++] = w); \
    }}while(0);

#define forin_kz(kz, Count, into, cur, w) forin_dz(kz, Count, into, cur, w)
#define forin_dan(dan, Count, into, cur, w) forin_dz(dan, Count, into, cur, w)

// 有几套
#define hasYOUJITAO(li, len, result) do{\
    for(auto i=0; i<len-1; i++)\
    {\
        if(li[i] == li[i+1] || li[i] == li[i+1]+1)\
        {\
            *(result)+=1;\
            i++;\
        }\
    }\
}while(0)

#endif // MJ_ANALYRESULT_H
