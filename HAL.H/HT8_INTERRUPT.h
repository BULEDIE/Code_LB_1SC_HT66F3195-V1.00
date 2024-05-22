
#ifndef _HT8_INTERRUPT_h_
#define _HT8_INTERRUPT_h_

/* interrupt control */
#define	EMI_ENABLE()			(_emi = 1)
#define	EMI_DISABLE()			(_emi = 0)

#define	MF0E_ENABLE()			(_mf0e = 1)
#define	MF0E_DISABLE()			(_mf0e = 0)
#define	MF0F_CLEAR_FLAG()		(_mf0f = 0)

#define	MF1E_ENABLE()			(_mf1e = 1)
#define	MF1E_DISABLE()			(_mf1e = 0)
#define	MF1F_CLEAR_FLAG()		(_mf1f = 0)

#define	MF2E_ENABLE()			(_mf2e = 1)
#define	MF2E_DISABLE()			(_mf2e = 0)
#define	MF2F_CLEAR_FLAG()		(_mf2f = 0)

#endif

