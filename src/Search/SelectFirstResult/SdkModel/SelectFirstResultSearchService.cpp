// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SelectFirstResultSearchService.h"
#include "SearchQueryPerformer.h"
#include "IMenuOption.h"
#include "ISearchResultRepository.h"
#include "IMenuModel.h"
#include "SearchResultItemModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SelectFirstResult
        {
            namespace SdkModel
            {
                SelectFirstResultSearchService::SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                     Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                               Menu::View::IMenuModel& menuModel)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultRepository(searchResultRepository)
                , m_menuModel(menuModel)
                , m_searchResultAddedCallback(this, &SelectFirstResultSearchService::OnSearchResultAdded)
                , m_didTransition(true)
                , m_deepLinkQuery("")
                {
                    m_searchResultRepository.InsertItemAddedCallback(m_searchResultAddedCallback);
                }
                
                SelectFirstResultSearchService::~SelectFirstResultSearchService()
                {
                    m_searchResultRepository.RemoveItemAddedCallback(m_searchResultAddedCallback);
                }
                
                void SelectFirstResultSearchService::PerformSearch(const std::string& queryString, const std::string& indoorMapId)
                {
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_searchQueryPerformer.PerformSearchQuery(queryString.c_str(), false, true, indoorMapId);
                    
                    m_didTransition = false;
                    m_deepLinkQuery = queryString;
                }
                
                void SelectFirstResultSearchService::OnSearchResultAdded(Search::SdkModel::SearchResultModel*& pSearchResultModel)
                {
                    if(!m_didTransition)
                    {
                        m_didTransition = true;
                        const std::string& query = m_searchQueryPerformer.GetPreviousSearchQuery().Query();
                        if(query == m_deepLinkQuery) // This is a workaround for when the PerformSearch return no results to stop this selecting the next search they do.
                        {
                            if(m_menuModel.GetItemCount() > 0)
                            {
                                m_menuModel.GetItemAtIndex(0).MenuOption().Select();
                            }
                        }
                    }
                }
            }
        }
    }
}


