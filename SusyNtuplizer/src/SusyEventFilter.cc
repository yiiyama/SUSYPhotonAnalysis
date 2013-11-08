#include "SusyEventFilter.h"

#include <cmath>

namespace susy {

  std::map<std::string, EventFilter> EventFilterDictionary::dictionary_;

  bool
  LooseDiphotonFilter(susy::Event const& _event)
  {
    susy::PhotonCollection const& photons(_event.photons.find("photons")->second);
    susy::SuperClusterCollection const& superClusters(_event.superClusters);

    unsigned nP(photons.size());
    unsigned nSel(0);

    for(unsigned iP(0); iP != nP; ++iP){
      susy::Photon const& photon(photons[iP]);
      if(photon.hadTowOverEm > 0.1) continue;
      if(photon.sigmaIetaIeta > 0.012) continue;

      if(photon.momentum.Pt() < 25.) continue;
      if(photon.superClusterIndex == -1) continue;
      susy::SuperCluster const& superCluster(superClusters[photon.superClusterIndex]);
      if(std::abs(superCluster.position.Eta()) > susy::etaGapBegin) continue;

      ++nSel;
    }

    return nSel > 1;
  }

  DEFINE_SUSYEVENTFILTER(LooseDiphotonFilter);

}
